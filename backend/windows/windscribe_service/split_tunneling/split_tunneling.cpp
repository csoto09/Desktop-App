#include "../all_headers.h"
#include "split_tunneling.h"
#include "../close_tcp_connections.h"
#include "../logger.h"
#include "../utils.h"

SplitTunneling::SplitTunneling(FirewallFilter &firewallFilter, FwpmWrapper &fwmpWrapper) : firewallFilter_(firewallFilter), calloutFilter_(fwmpWrapper), 
				 hostnamesManager_(firewallFilter), isSplitTunnelEnabled_(false), isExclude_(false), bKeepLocalSockets_(false), prevIsSplitTunnelActive_(false), prevIsExclude_(false)
{
	connectStatus_.isConnected = false;
	detectWindscribeExecutables();
}

SplitTunneling::~SplitTunneling()
{
	assert(isSplitTunnelEnabled_ == false);
}

void SplitTunneling::setSettings(bool isEnabled, bool isExclude, const std::vector<std::wstring> &apps, const std::vector<std::wstring> &ips, const std::vector<std::string> &hosts)
{
	isSplitTunnelEnabled_ = isEnabled;
	isExclude_ = isExclude;

	apps_ = apps;

	std::vector<Ip4AddressAndMask> ipsList;
	for (auto it = ips.begin(); it != ips.end(); ++it)
	{
		ipsList.push_back(Ip4AddressAndMask(it->c_str()));
	}
	hostnamesManager_.setSettings(isExclude, ipsList, hosts);

	routesManager_.updateState(connectStatus_, isSplitTunnelEnabled_, isExclude_);
	updateState();	
}

void SplitTunneling::setConnectStatus(CMD_CONNECT_STATUS &connectStatus)
{
	connectStatus_ = connectStatus;
	routesManager_.updateState(connectStatus_, isSplitTunnelEnabled_, isExclude_);
	updateState();
}


void SplitTunneling::removeAllFilters(FwpmWrapper &fwmpWrapper)
{
	CalloutFilter::removeAllFilters(fwmpWrapper);
}

void SplitTunneling::detectWindscribeExecutables()
{
	std::wstring exePath = Utils::getExePath();
	std::wstring fileFilter = exePath + L"\\*.exe";

	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFileEx(fileFilter.c_str(), FindExInfoBasic, &ffd, FindExSearchNameMatch, NULL, 0);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	std::vector<std::wstring> windscribeExeFiles;
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			std::wstring f = exePath + L"\\" + ffd.cFileName;
			windscribeExeFiles.push_back(f);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);

	windscribeExecutablesIds_.setFromList(windscribeExeFiles);
}

void SplitTunneling::updateState()
{
	bool isSplitTunnelActive = connectStatus_.isConnected && isSplitTunnelEnabled_;

	if (isSplitTunnelActive)
	{
		splitTunnelServiceManager_.start();

		DWORD redirectIp;
		AppsIds appsIds;
		appsIds.setFromList(apps_);

		if (isExclude_)
		{
			Ip4AddressAndMask ipAddress(connectStatus_.defaultAdapter.adapterIp.c_str());
			redirectIp = ipAddress.ipNetworkOrder();
			hostnamesManager_.enable(connectStatus_.defaultAdapter.gatewayIp, connectStatus_.defaultAdapter.ifIndex);
		}
		else
		{
			appsIds.addFrom(windscribeExecutablesIds_);
		
			Ip4AddressAndMask ipAddress(connectStatus_.vpnAdapter.adapterIp.c_str());
			redirectIp = ipAddress.ipNetworkOrder();	

			if (connectStatus_.protocol == CMD_PROTOCOL_OPENVPN || connectStatus_.protocol == CMD_PROTOCOL_STUNNEL_OR_WSTUNNEL)
			{
				hostnamesManager_.enable(connectStatus_.vpnAdapter.gatewayIp, connectStatus_.vpnAdapter.ifIndex);
			}
			else if ((connectStatus_.protocol == CMD_PROTOCOL_IKEV2 || connectStatus_.protocol == CMD_PROTOCOL_WIREGUARD))
			{
				hostnamesManager_.enable(connectStatus_.vpnAdapter.adapterIp, connectStatus_.vpnAdapter.ifIndex);
			}
		}

		calloutFilter_.enable(redirectIp, appsIds);
	}
	else
	{
		calloutFilter_.disable();
		hostnamesManager_.disable();
		splitTunnelServiceManager_.stop();
	}

	// close TCP sockets if state changed
	bool bNeedCloseTcpSockets = false;
	if (isSplitTunnelActive != prevIsSplitTunnelActive_)
	{
		bNeedCloseTcpSockets = true;
	}
	else if (isSplitTunnelActive && isExclude_ != prevIsExclude_)
	{
		bNeedCloseTcpSockets = true;
	}
	prevIsSplitTunnelActive_ = isSplitTunnelActive;
	prevIsExclude_ = isExclude_;

	if (bNeedCloseTcpSockets)
	{
		Logger::instance().out(L"SplitTunneling::threadFunc() close all TCP sockets");
		CloseTcpConnections::closeAllTcpConnections(bKeepLocalSockets_);
	}
}