#include "parseovpnconfigline.h"

ParseOvpnConfigLine::OpenVpnLine ParseOvpnConfigLine::processLine(const QString &line)
{
    OpenVpnLine openVpnLine;
    openVpnLine.type = OVPN_CMD_UNKNOWN;

    if (line.contains("remote", Qt::CaseInsensitive))
    {
        QStringList strs = splitLine(line);

        if (strs.count() > 0 && strs[0].compare("remote", Qt::CaseInsensitive) == 0)
        {
            if (strs.count() >= 2)
            {
                openVpnLine.type = OVPN_CMD_REMOTE_IP;
                openVpnLine.host = strs[1];

                if (strs.count() >= 3)
                {
                    openVpnLine.port = strs[2].toUInt();

                    if (strs.count() >= 4)
                    {
                        openVpnLine.protocol = strs[3];
                    }
                }
            }
        }
    }
    else if (line.contains("proto", Qt::CaseInsensitive))
    {
        QStringList strs = splitLine(line);

        if (strs.count() > 0 && strs[0].compare("proto", Qt::CaseInsensitive) == 0)
        {
            if (strs.count() >= 2)
            {
                openVpnLine.type = OVPN_CMD_PROTO;
                openVpnLine.protocol = strs[1];
            }
        }
    }
    else if (line.contains("port", Qt::CaseInsensitive))
    {
        QStringList strs = splitLine(line);

        if (strs.count() > 0 && strs[0].compare("port", Qt::CaseInsensitive) == 0)
        {
            if (strs.count() >= 2)
            {
                openVpnLine.type = OVPN_CMD_PORT;
                openVpnLine.port = strs[1].toUInt();
            }
        }
    }

    return openVpnLine;
}

QStringList ParseOvpnConfigLine::splitLine(const QString &line)
{
    QStringList res;
    int i = 0;
    QString curString;
    bool isInsideString = false;
    bool isInsideQuetes = false;

    while (i < line.count())
    {
        if (isInsideString)
        {
            if (isInsideQuetes)
            {
                curString += line[i];
                if (line[i] == '\'' || line[i] == '\"')
                {
                    isInsideQuetes = false;
                    isInsideString = false;
                    res << curString;
                    curString.clear();
                }
            }
            else
            {
                if (line[i].isSpace())
                {
                    isInsideString = false;
                    res << curString;
                    curString.clear();
                }
                else
                {
                    curString += line[i];
                }
            }
        }
        else
        {
            if (line[i] == '\'' || line[i] == '\"')
            {
                isInsideQuetes = true;
                isInsideString = true;
                curString += line[i];
            }
            else if (!line[i].isSpace())
            {
                isInsideQuetes = false;
                isInsideString = true;
                curString += line[i];
            }
        }
        i++;
    }

    if (!curString.isEmpty())
    {
        res << curString;
    }
    return res;
}