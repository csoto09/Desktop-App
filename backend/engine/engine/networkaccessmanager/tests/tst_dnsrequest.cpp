#include <QtTest>
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <WinSock2.h>
#include "tst_dnsrequest.h"
#include "../networkaccessmanager/dnsresolver/dnsrequest.h"


TestDnsRequest::TestDnsRequest()
{
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    // random test domains
    const std::string strs[] = { "google.com",
    "facebook.com",
    "doubleclick.net",
    "google-analytics.com",
    "akamaihd.net",
    "googlesyndication.com",
    "googleapis.com",
    "googleadservices.com",
    "facebook.net",
    "youtube.com",
    "twitter.com",
    "scorecardresearch.com",
    "microsoft.com",
    "ytimg.com",
    "googleusercontent.com",
    "apple.com",
    "msftncsi.com",
    "2mdn.net",
    "googletagservices.com",
    "adnxs.com",
    "yahoo.com",
    "serving-sys.com",
    "akadns.net",
    "bluekai.com",
    "ggpht.com",
    "rubiconproject.com",
    "verisign.com",
    "addthis.com",
    "crashlytics.com",
    "amazonaws.com",
    "quantserve.com",
    "akamaiedge.net",
    "live.com",
    "googletagmanager.com",
    "revsci.net",
    "adadvisor.net",
    "openx.net",
    "digicert.com",
    "pubmatic.com",
    "agkn.com",
    "instagram.com",
    "mathtag.com",
    "gmail.com",
    "rlcdn.com",
    "linkedin.com",
    "yahooapis.com",
    "chartbeat.net",
    "twimg.com",
    "turn.com",
    "crwdcntrl.net",
    "demdex.net",
    "betrad.com",
    "flurry.com",
    "newrelic.com",
    "yimg.com",
    "youtube-nocookie.com",
    "exelator.com",
    "acxiom-online.com",
    "imrworldwide.com",
    "amazon.com",
    "fbcdn.net",
    "windowsupdate.com",
    "mookie1.com",
    "rfihub.com",
    "omniroot.com",
    "adsrvr.org",
    "nexac.com",
    "bing.com",
    "skype.com",
    "godaddy.com",
    "sitescout.com",
    "tubemogul.com",
    "contextweb.com",
    "w55c.net",
    "chartbeat.com",
    "akamai.net",
    "jquery.com",
    "adap.tv",
    "criteo.com",
    "krxd.net",
    "optimizely.com",
    "macromedia.com",
    "comodoca.com",
    "casalemedia.com",
    "pinterest.com",
    "adsymptotic.com",
    "symcd.com",
    "atwola.com",
    "adobe.com",
    "msn.com",
    "adsafeprotected.com",
    "tapad.com",
    "truste.com",
    "symantecliveupdate.com",
    "atdmt.com",
    "t.co",
    "avast.com",
    "google.co.in",
    "spotxchange.com",
    "tidaltv.com",
    "tidaltv.com",
    "adtechus.com",
    "everesttech.net",
    "addthisedge.com",
    "hola.org",
    "btrll.com",
    "gwallet.com",
    "liverail.com",
    "windows.com",
    "burstnet.com",
    "disqus.com",
    "nr-data.net",
    "p-td.com",
    "geotrust.com",
    "admob.com",
    "crittercism.com",
    "bizographics.com",
    "ru4.com",
    "wtp101.com",
    "ksmobile.com",
    "msads.net",
    "thawte.com",
    "lijit.com",
    "cloudflare.com",
    "360yield.com",
    "dropbox.com",
    "simpli.fi",
    "smartadserver.com",
    "globalsign.com",
    "mlnadvertising.com",
    "chango.com",
    "connexity.net",
    "moatads.com",
    "s-msn.com",
    "entrust.net",
    "tribalfusion.com",
    "domdex.com",
    "google.com.tr",
    "whatsapp.net",
    "ntp.org",
    "amazon-adsystem.com",
    "viber.com",
    "disquscdn.com",
    "yandex.ru",
    "doubleverify.com",
    "bkrtx.com",
    "criteo.net",
    "outbrain.com",
    "questionmarket.com",
    "adform.net",
    "yieldmanager.com",
    "typekit.net",
    "goo.gl",
    "voicefive.com",
    "owneriq.net",
    "media6degrees.com",
    "tynt.com",
    "symcb.com",
    "advertising.com",
    "audienceiq.com",
    "wp.com",
    "rtbidder.net",
    "wikipedia.org",
    "adroll.com",
    "icloud.com",
    "gravatar.com",
    "collective-media.net",
    "appsflyer.com",
    "dmtry.com",
    "blogger.com",
    "taboola.com",
    "legolas-media.com",
    "images-amazon.com",
    "afy11.net",
    "aspnetcdn.com",
    "hike.in",
    "feedburner.com",
    "bootstrapcdn.com",
    "usertrust.com",
    "adgrx.com",
    "brilig.com",
    "sharethis.com",
    "flashtalking.com",
    "mediaplex.com",
    "eqads.com",
    "adscale.de",
    "imgur.com",
    "edgesuite.net",
    "blogspot.com",
    "msocsp.com",
    "wikimedia.org",
    "ssl-images-amazon.com",
    "amung.us",
    "flickr.com",
    "rundsp.com",
    "trouter.io",
    "edgekey.net",
    "rfihub.net",
    "utorrent.com",
    "thebrighttag.com",
    "eyeviewads.com",
    "switchads.com",
    "tiqcdn.com",
    "mozilla.org",
    "jwpcdn.com",
    "exponential.com",
    "abmr.net",
    "nanigans.com",
    "zenoviaexchange.com",
    "yashi.com",
    "jumptap.com",
    "interclick.com",
    "tapjoyads.com",
    "globalsign.net",
    "eyereturn.com",
    "pointroll.com",
    "googlevideo.com",
    "virtualearth.net",
    "gumgum.com",
    "triggit.com",
    "tumblr.com",
    "gigya.com",
    "teamviewer.com",
    "insightexpressai.com",
    "msecnd.net",
    "gemius.pl",
    "oracle.com",
    "sonobi.com",
    "fastclick.net",
    "ebay.com",
    "adobetag.com",
    "surveymonkey.com",
    "stumbleupon.com",
    "admaym.com",
    "invitemedia.com",
    "superfish.com",
    "google.com.vn",
    "yahoodns.net",
    "tapjoy.com",
    "blogblog.com",
    "mxpnl.com",
    "omtrdc.net",
    "skimresources.com",
    "akamai.com",
    "adobedtm.com",
    "starfieldtech.com",
    "skypeassets.com",
    "a.com",
    "btstatic.com",
    "researchnow.com",
    "conviva.com",
    "hotmail.com",
    "bittorrent.com",
    "openbittorrent.com",
    "vindicosuite.com",
    "duba.net",
    "publicbt.com",
    "impact-ad.jp",
    "netflix.com",
    "ib-ibi.com",
    "smaato.net",
    "netsolssl.com",
    "fetchback.com",
    "appspot.com",
    "vk.com",
    "mozilla.com",
    "accu-weather.com",
    "yieldmanager.net",
    "yadro.ru",
    "histats.com",
    "netseer.com",
    "creativecommons.org",
    "live.net",
    "vizu.com",
    "youtu.be",
    "kau.li",
    "eyeota.net",
    "weather.com",
    "provenpixel.com",
    "veruta.com",
    "umengcloud.com",
    "paypal.com",
    "office365.com",
    "simplereach.com",
    "ooyala.com",
    "specificclick.net",
    "digg.com",
    "google.ca",
    "dotomi.com",
    "netmng.com",
    "undertone.com",
    "erne.co",
    "staticflickr.com",
    "urbanairship.com",
    "adkmob.com",
    "pro-market.net",
    "dtscout.com",
    "imdb.com",
    "mzstatic.com",
    "alexa.com",
    "fastly.net",
    "baidu.com",
    "brealtime.com",
    "amazon.co.uk",
    "midasplayer.com",
    "bugsense.com",
    "outlook.com",
    "chartboost.com",
    "adrta.com",
    "adcash.com",
    "root-servers.net",
    "adtilt.com",
    "awstls.com",
    "fwmrm.net",
    "cdninstagram.com",
    "adsonar.com",
    "zedo.com",
    "demonii.com",
    "vimeo.com",
    "dianxinos.com",
    "adventori.com",
    "accuweather.com",
    "steamstatic.com",
    "coull.com",
    "mxptint.net",
    "pfx.ms",
    "footprint.net",
    "ceipmsn.com",
    "paypalobjects.com",
    "taboolasyndication.com",
    "umeng.com",
    "altitude-arena.com",
    "webtrendslive.com",
    "dl-rms.com",
    "visualwebsiteoptimizer.com",
    "mydas.mobi",
    "cap-mii.net",
    "naver.jp",
    "avg.com",
    "wordpress.com",
    "pinimg.com",
    "livefyre.com",
    "tabwpm.us",
    "maxymiser.net",
    "wordpress.org",
    "ebayimg.com",
    "gravity.com",
    "huffingtonpost.com",
    "exoclick.com",
    "pandora.com",
    "reson8.com",
    "grvcdn.com",
    "aol.com",
    "adcolony.com",
    "adhigh.net",
    "eset.com",
    "trustwave.com",
    "cnn.com",
    "cxense.com",
    "lfstmedia.com",
    "xboxlive.com",
    "vungle.com",
    "a3cloud.net",
    "dailymotion.com",
    "postrelease.com",
    "duapp.com",
    "king.com",
    "mailshell.net",
    "pingdom.net",
    "lenovomm.com",
    "dyntrk.com",
    "kaspersky-labs.com",
    "jwpsrv.com",
    "nsatc.net",
    "soundcloud.com",
    "vimeocdn.com",
    "theviilage.com",
    "hlserve.com",
    "wdgserv.com",
    "inmobi.com",
    "bbc.co.uk",
    "kaspersky.com",
    "spotxcdn.com",
    "norton.com",
    "nytimes.com",
    "crsspxl.com",
    "liveperson.net",
    "amgdgt.com",
    "amazon.in",
    "amazon.de",
    "adotube.com",
    "go.com",
    "samsungosp.com",
    "parsely.com",
    "windowsphone.com",
    "heias.com",
    "amazon.it",
    "washingtonpost.com",
    "ospserver.net",
    "mscimg.com",
    "google.co.uk",
    "mzl.la",
    "pswec.com",
    "media.net",
    "v0cdn.net",
    "supercell.net",
    "visadd.com",
    "andomedia.com",
    "mdotlabs.com",
    "adformdsp.net",
    "wikimediafoundation.org",
    "alenty.com",
    "zergnet.com",
    "sundaysky.com",
    "amazon.ca",
    "mediawiki.org",
    "datafastguru.info",
    "vidible.tv",
    "adzerk.net",
    "brand-server.com",
    "quantcount.com",
    "flipboard.com",
    "dtmpub.com",
    "sail-horizon.com",
    "applovin.com",
    "nspmotion.com",
    "metrigo.com",
    "pulsemgr.com",
    "visiblemeasures.com",
    "revenuemantra.com",
    "smartclip.net",
    "ijinshan.com",
    "tndmnsha.com",
    "go-mpulse.net",
    "relestar.com",
    "amazon.co.jp",
    "jollywallet.com",
    "trafficmanager.net",
    "imgfarm.com",
    "opera-mini.net",
    "cogocast.net",
    "onenote.com",
    "amazon.es",
    "opendns.com",
    "p161.net",
    "a-msedge.net",
    "cpmstar.com",
    "amazon.com.br",
    "logmein.com",
    "nflximg.net",
    "univide.com",
    "tekblue.net",
    "infostatsvc.com",
    "udmserve.net",
    "basebanner.com",
    "zynga.com",
    "amazon.cn",
    "mathads.com",
    "amazon.com.au",
    "mediade.sk",
    "atemda.com",
    "d41.co",
    "amazon.com.mx",
    "airpush.com",
    "ksmobile.net",
    "geogslb.com",
    "goodreads.com",
    "monetate.net",
    "clicktale.net",
    "richrelevance.com",
    "tns-counter.ru",
    "coremetrics.com",
    "online-metrix.net",
    "rs6.net",
    "xingcloud.com",
    "generalmobi.com",
    "uservoice.com",
    "herokuapp.com",
    "adblade.com",
    "svcmot.com",
    "shopbop.com",
    "z5x.net",
    "optmd.com",
    "dropboxusercontent.com",
    "fbsbx.com",
    "turner.com",
    "onclickads.net",
    "bookdepository.com",
    "bluecava.com",
    "adtimaserver.vn",
    "beringmedia.com",
    "choicestream.com",
    "zanox.com",
    "apsalar.com",
    "realmedia.com",
    "dpclk.com",
    "cedexis.com",
    "scanscout.com",
    "display-trk.com",
    "bitmedianetwork.com",
    "ctnsnet.com",
    "tunigo.com",
    "samsung.com",
    "bazaarvoice.com",
    "ebayrtm.com",
    "returnpath.net",
    "walmart.com",
    "wsod.com",
    "constantcontact.com",
    "getclicky.com",
    "localytics.com",
    "ligatus.com",
    "appier.net",
    "dxsvr.com",
    "myhabit.com",
    "ajaxcdn.org",
    "adyapper.com",
    "nist.gov",
    "neulion.com",
    "edgecastcdn.net",
    "convertro.com",
    "vnexpress.net",
    "javafx.com",
    "thepiratebay.org",
    "skype.net",
    "kontagent.net",
    "newsinc.com",
    "glpals.com",
    "ebz.io",
    "audible.com",
    "mobogenie.com",
    "dingaling.ca",
    "nrcdn.com",
    "stumble-upon.com",
    "backupgrid.net",
    "po.st",
    "marinsm.com",
    "nflximg.com",
    "adizio.com",
    "acx.com",
    "fyre.co",
    "admedo.com",
    "xvideos.com",
    "junglee.com",
    "evernote.com",
    "createspace.com",
    "buzzfeed.com",
    "zing.vn",
    "sanasecurity.com",
    "igexin.com",
    "bnmla.com",
    "liadm.com",
    "usatoday.com",
    "scanalert.com",
    "espncdn.com",
    "metamx.com",
    "plexop.net",
    "optimatic.com",
    "medyanetads.com",
    "w3.org",
    "apnanalytics.com",
    "gezinti.com",
    "dpreview.com",
    "xbox.com",
    "servesharp.net",
    "cpxinteractive.com",
    "adsparc.net",
    "cardlytics.com",
    "dailymail.co.uk",
    "redditstatic.com",
    "sociomantic.com",
    "contentabc.com",
    "admost.com",
    "inmobicdn.net",
    "3g.cn",
    "miisolutions.net",
    "nrelate.com",
    "innovid.com",
    "nola.com",
    "testflightapp.com",
    "teads.tv",
    "fool.com",
    "tripadvisor.com",
    "al.com",
    "cloudapp.net",
    "public-trust.com",
    "vine.co",
    "mlive.com",
    "ad4game.com",
    "ask.com",
    "networkhm.com",
    "amazonlocal.com",
    "zappos.com",
    "diapers.com",
    "adtricity.com",
    "ml314.com",
    "yldbt.com",
    "plexop.com",
    "bbb.org",
    "tworismo.com",
    "amazonsupply.com",
    "beautybar.com",
    "theguardian.com",
    "myhomemsn.com",
    "nvidia.com",
    "comixology.com",
    "bookworm.com",
    "huffpost.com",
    "vcmedia.vn",
    "casa.com",
    "woot.com",
    "eastdane.com",
    "answers.com",
    "infolinks.com",
    "fabric.com",
    "lphbs.com",
    "rpxnow.com",
    "ovi.com",
    "dlinksearch.com",
    "adlooxtracking.com",
    "soap.com",
    "mail.ru",
    "look.com",
    "microsoftonline.com",
    "wag.com",
    "dyndns.org",
    "pennlive.com",
    "nbcnews.com",
    "yoyo.com",
    "zopim.com",
    "collserve.com",
    "vine.com",
    "gpsonextra.net",
    "tacoda.net",
    "trusteer.com",
    "yahoo.net",
    "toolbarservices.com",
    "bluelithium.com",
    "sun.com",
    "33across.com",
    "ipinfo.io",
    "iasds01.com",
    "longtailvideo.com",
    "typography.com",
    "6pm.com",
    "ptvcdn.net",
    "adf.ly",
    "kissmetrics.com",
    "ccc.de",
    "c3tag.com",
    "safemovedm.com",
    "tango.me",
    "bbc.com",
    "syracuse.com",
    "dashbida.com",
    "gvt1.com",
    "admicro.vn",
    "sascdn.com",
    "r1-cdn.net",
    "everestjs.net",
    "craigslist.org",
    "llnwd.net",
    "thanksearch.com",
    "iegallery.com",
    "typekit.com",
    "visualdna.com",
    "angsrvr.com",
    "tenmarks.com",
    "mediaforge.com",
    "telegraph.co.uk",
    "myspace.com",
    "lastpass.com",
    "steampowered.com",
    "startssl.com",
    "ipinyou.com",
    "fonts.net",
    "goo.mx",
    "google.com.mx",
    "tr553.com",
    "5min.com",
    "tfxiq.com",
    "korrelate.net",
    "alibaba.com",
    "mininova.org",
    "ebaydesc.com",
    "desync.com",
    "compete.com",
    "kochava.com",
    "kaltura.com",
    "bleacherreport.com",
    "buscape.com.br",
    "flite.com",
    "swisssign.net",
    "yieldmo.com",
    "content.ad",
    "github.com",
    "wsj.com",
    "opera.com",
    "grouponcdn.com",
    "aliunicorn.com",
    "solocpm.com",
    "nav-links.com",
    "crtinv.com",
    "hiro.tv",
    "opendsp.com",
    "windows.net",
    "dmcdn.net",
    "wii.com",
    "farlex.com",
    "smartstream.tv",
    "yandex.net",
    "masslive.com",
    "blogher.org",
    "jccjd.com",
    "beanstock.co",
    "weatherbug.com",
    "intellitxt.com",
    "bidtheatre.com",
    "mmondi.com",
    "linkedinlabs.com",
    "acrobat.com",
    "nokia.com",
    "levexis.com",
    "cbsi.com",
    "adsplats.com",
    "perfectaudience.com",
    "admarvel.com",
    "performgroup.com",
    "liveinternet.ru",
    "zyngawithfriends.com",
    "bankrate.com",
    "24h.com.vn",
    "trafficjunky.net",
    "cedexis.net",
    "janrain.com",
    "geforce.com",
    "tacdn.com",
    "eonline.com",
    "smarturl.it",
    "impdesk.com",
    "internapcdn.net",
    "umeng.co",
    "sekindo.com",
    "steamcommunity.com",
    "riotgames.com",
    "wunderground.com",
    "nextadvisor.com",
    "reuters.com",
    "vibrant.co",
    "blackberry.com",
    "hwcdn.net",
    "tremormedia.com",
    "netgear.com",
    "fncstatic.com",
    "google.com.eg",
    "ebdr3.com",
    "revcontent.com",
    "businessinsider.com",
    "prfct.co",
    "iperceptions.com",
    "c8.net.ua",
    "taobao.com",
    "delicious.com",
    "247realmedia.com",
    "imwx.com",
    "active-agent.com",
    "supersonicads.com",
    "realtime.co",
    "kill123.com",
    "phncdn.com",
    "redditmedia.com",
    "thepostgame.com",
    "h33t.com",
    "a9.com",
    "foursquare.com",
    "milliyet.com.tr",
    "4dsply.com",
    "upwpm.us",
    "csze.com",
    "mediaquark.com",
    "tritondigital.com",
    "mozilla.net",
    "fidelity-media.com",
    "dmca.com",
    "greystripe.com",
    "cafemom.com",
    "mapticket.net",
    "xhamster.com",
    "ow.ly",
    "maxmind.com",
    "avira.com",
    "webspectator.com",
    "marketo.net",
    "vlingo.com",
    "linkwithin.com",
    "latimes.com",
    "cbsnews.com",
    "eclick.vn",
    "glbimg.com",
    "epicunitscan.info",
    "avira-update.com",
    "hoptopboy.com",
    "tvlsvc.com",
    "tailtarget.com",
    "desk.com",
    "intentiq.com",
    "ero-advertising.com",
    "imguol.com",
    "everyscreenmedia.com",
    "bbci.co.uk",
    "itunes.com",
    "engadget.com",
    "people.com",
    "dsply.com",
    "voga360.com",
    "hmageo.com",
    "337play.com",
    "gannett-cdn.com",
    "rcsadv.it",
    "manage.com",
    "cachefly.net",
    "doublepimp.com",
    "keen.io",
    "ea.com",
    "reklamport.com",
    "shopping.com",
    "youradexchange.com",
    "hp.com",
    "apptentive.com",
    "earthnetworks.com",
    "nfl.com",
    "userdmp.com",
    "yastatic.net",
    "google.de",
    "apxlv.com",
    "moneynews.com",
    "livechatinc.com",
    "forbes.com",
    "pornhub.com",
    "sbal4kp.com",
    "wsoddata.com",
    "logmein-gateway.com",
    "facdn.com",
    "yldmgrimg.net",
    "hurriyet.com.tr",
    "lucidmedia.com",
    "doracdn.com",
    "indeed.com",
    "disneytermsofuse.com",
    "truecaller.com",
    "time.com",
    "mediatek.com",
    "ioam.de",
    "rackcdn.com",
    "baidu.co.th",
    "reklamstore.com",
    "pricegrabber.com",
    "dyndns.com",
    "imageshack.us",
    "popads.net",
    "dataxu.com",
    "sndcdn.com",
    "gizmodo.com",
    "imageshack.com",
    "yelp.com",
    "google.ru",
    "best-tv.com",
    "webtrends.com",
    "google.fr",
    "archive.org",
    "walmartimages.com",
    "att.com",
    "e-planning.net",
    "openxenterprise.com",
    "yan.vn",
    "company-target.com",
    "cmptch.com",
    "incmd04.com",
    "disneyprivacycenter.com",
    "npr.org",
    "tellapart.com",
    "hulu.com",
    "dynamicyield.com",
    "theatlantic.com",
    "atgsvcs.com",
    "whois.co.kr",
    "life360.com",
    "tmz.com",
    "visualstudio.com",
    "adservingml.com",
    "securetrust.com",
    "qubitproducts.com",
    "360.cn",
    "realvu.net",
    "fortune.com",
    "sitescoutadserver.com",
    "sponsorpay.com",
    "torrentum.pl",
    "brcdn.com",
    "origin.com",
    "slidesharecdn.com",
    "360safe.com",
    "pressroomvip.com",
    "unrulymedia.com",
    "nxtck.com",
    "adexcite.com",
    "etsy.com",
    "odnoklassniki.ru",
    "iheart.com",
    "mmstat.com",
    "glam.com",
    "radaronline.com",
    "popnhop.com",
    "edgefcs.net",
    "redintelligence.net",
    "myvisualiq.net",
    "mgid.com",
    "2o7.net",
    "mapquest.com",
    "mediamath.com",
    "me.com",
    "ugdturner.com",
    "amasvc.com",
    "monster.com",
    "seethisinaction.com",
    "ebayinc.com",
    "wallstcheatsheet.com",
    "sogou.com",
    "ambient-platform.com",
    "traffichaus.com",
    "kinja-img.com",
    "googlecommerce.com",
    "utorrent.li",
    "thoiloan.vn",
    "dantri.com.vn",
    "ubuntu.com",
    "wlxrs.com",
    "adscience.nl",
    "shoppingshadow.com",
    "mradx.net",
    "fotapro.com",
    "wired.com",
    "cdn.md",
    "hubspot.com",
    "google.es",
    "buzzfed.com",
    "comcast.net",
    "polldaddy.com",
    "plexapp.com",
    "hidemyass.com",
    "steelhousemedia.com",
    "yumenetworks.com",
    "acc-hd.de",
    "populisengage.com",
    "bncnt.com",
    "responsys.net",
    "printfriendly.com",
    "zendesk.com",
    "gmtdmp.com",
    "madisonlogic.com",
    "dartsearch.net",
    "zdn.vn",
    "zedo.net",
    "nbcudigitaladops.com",
    "stubhub.com",
    "adhood.com",
    "microsofttranslator.com",
    "espn.com",
    "linksmart.com",
    "wshifen.com",
    "appa-maker.com",
    "cabelas.com",
    "redtube.com",
    "channelintelligence.com",
    "dell.com",
    "weibo.com",
    "channeladvisor.com",
    "viewster.com",
    "adjuggler.net",
    "xnxx.com",
    "adxpansion.com",
    "alibench.com",
    "qadservice.com",
    "mybuys.com",
    "raasnet.com",
    "tanx.com",
    "popmarker.com",
    "pubnub.com",
    "peer39.net",
    "globo.com",
    "weborama.fr",
    "independent.co.uk",
    "searchmarketing.com",
    "zemanta.com",
    "vgtf.net",
    "inspsearchapi.com",
    "rambler.ru",
    "en25.com",
    "gomonetworks.com",
    "playhaven.com",
    "aweber.com",
    "retargetly.com",
    "allvoices.com",
    "intel.com",
    "pubsqrd.com",
    "admized.com",
    "minimob.com",
    "adingo.jp",
    "cnet.com",
    "userreport.com",
    "trustedsource.org",
    "vk.me",
    "mediafire.com",
    "buysellads.com",
    "slideshare.net",
    "sexad.net",
    "windowsmedia.com",
    "tremorhub.com",
    "licasd.com",
    "bycontext.com",
    "echoenabled.com",
    "issuu.com",
    "1mobile.com",
    "corporate-ir.net",
    "pubexchange.com",
    "audienceinsights.net",
    "adobur.com",
    "celtra.com",
    "techcrunch.com",
    "boo-box.com",
    "eum-appdynamics.com",
    "try9.com",
    "adriver.ru",
    "taobaocdn.com",
    "dealtime.com",
    "ed4.net",
    "trust-provider.com",
    "feedbackify.com",
    "bbelements.com",
    "dwin1.com",
    "yandex.st",
    "gssp-a.com",
    "4seeresults.com",
    "adition.com",
    "nhncorp.jp",
    "googlemail.com",
    "about.com",
    "gap.com",
    "hotwords.com.br",
    "ant.com",
    "plugrush.com",
    "foreseeresults.com",
    "bidswitch.net",
    "gawker.com",
    "advidi.com",
    "pagefair.net",
    "mixpo.com",
    "intuit.com",
    "imiclk.com",
    "bestbuy.com",
    "engageya.com",
    "nexage.com",
    "intergi.com",
    "playstation.net",
    "foxbusiness.com",
    "adk2.com",
    "9999mb.com",
    "bitdefender.net",
    "cpserve.com",
    "yb0t.com",
    "mi-idc.com",
    "espn.co.uk",
    "minecraft.net",
    "crossrider.com",
    "conduit.com",
    "sensic.net",
    "pavv.co.kr",
    "telemetryverification.net",
    "metanetwork.net",
    "lifehacker.com",
    "bbcimg.co.uk",
    "today.com",
    "jtvnw.net",
    "ptreklam.com.tr",
    "inspsearch.com",
    "poll.fm",
    "komoona.com",
    "v2cdn.net",
    "adtima.vn",
    "viralnova.com",
    "harry.lu",
    "trialpay.com",
    "m6r.eu",
    "samsungrm.net",
    "vindicosuitecache.com",
    "rarbg.me",
    "pusherapp.com",
    "asus.com",
    "indexww.com",
    "assoc-amazon.com",
    "ask.fm",
    "yandex.com.tr",
    "adpredictive.com",
    "swiftkey.net",
    "csdata1.com",
    "kontera.com",
    "reddit.tv",
    "baidustatic.com",
    "ctmail.com",
    "gotinder.com",
    "siteadvisor.com",
    "applifier.com",
    "gtimg.com",
    "crdrdpjs.info",
    "redditgifts.com",
    "boldchat.com",
    "dataxu.net",
    "wishabi.net",
    "dynad.net",
    "legacy.com",
    "emjcd.com",
    "cbsimg.net",
    "google.com.hk",
    "pop6.com",
    "t-mobile.com",
    "anthill.vn",
    "zdbb.net",
    "sitewebred.info",
    "youporn.com",
    "radiumone.com",
    "whatsapp.com",
    "technorati.com",
    "aim.net",
    "dotandad.com",
    "ex.ua",
    "adsrvmedia.net",
    "lineage2.com.cn",
    "metaffiliation.com",
    "mywot.com",
    "ns-img.com",
    "shoplocal.com",
    "cloudinary.com",
    "creativecdn.com",
    "vdna-assets.com",
    "doi.org",
    "newsmaxfeednetwork.com",
    "rantlifestyle.com",
    "thedailybeast.com",
    "adjuggler.com",
    "huffpo.net",
    "shopify.com",
    "bitly.com",
    "trtromg.com",
    "samsungotn.net",
    "ups.com",
    "hlntv.com",
    "spccint.com",
    "domobile.com",
    "shinystat.com",
    "worldssl.net",
    "infospace.com",
    "chtah.com",
    "vaporcloudcomputing.com",
    "firstimpwins.com",
    "factual.com",
    "ad360.vn",
    "nmcdn.us",
    "adgear.com",
    "theverge.com",
    "mapquestapi.com",
    "comodoca2.com",
    "scdn.co",
    "sstatic.net",
    "kgridhub.com",
    "coccoc.com",
    "businessweek.com",
    "etonline.com",
    "olx.com",
    "eepurl.com",
    "inspectlet.com",
    "marketwatch.com",
    "rklyjs.info",
    "googledrive.com",
    "ford.com",
    "ants.vn",
    "comufy.com",
    "adshost1.com",
    "ns-cdn.com",
    "q1mediahydraplatform.com",
    "tmall.com",
    "booking.com",
    "fivethirtyeight.com",
    "juicyads.com",
    "groovinads.com",
    "plug.it",
    "myvzw.com",
    "semasio.net",
    "nih.gov",
    "cbsinteractive.com",
    "gandi.net",
    "appclick.co",
    "githubusercontent.com",
    "gogorithm.com",
    "openweathermap.org",
    "directrev.com",
    "pow7.com",
    "io9.com",
    "ok.ru",
    "cdnads.com",
    "updatepm.com",
    "chitika.net",
    "vnecdn.net",
    "sailthru.com",
    "fb.me",
    "zencdn.net",
    "salon.com",
    "espnfc.us",
    "mouseflow.com",
    "mainadv.com",
    "healthcentral.com",
    "novanet.vn",
    "civicscience.com",
    "ft.com",
    "worldnow.com",
    "charter.com",
    "polyad.net",
    "si.com",
    "webengage.com",
    "mobfox.com",
    "google.nl",
    "millennialmedia.com",
    "dataferb.com",
    "vkontakte.ru",
    "ff0000-cdn.net",
    "billboard.com",
    "beanstock.com",
    "mochibot.com",
    "wiktionary.org",
    "cnn.co.jp",
    "blankbase.com",
    "fedex.com",
    "ywxi.net",
    "sitemeter.com",
    "ap.org",
    "vitrinesglobo.com.br",
    "admission.net",
    "unity3d.com",
    "zedge.net",
    "hackerwatch.org",
    "gameanalytics.com",
    "wistia.com",
    "petuniasaucecockup.com",
    "whaleserver.com",
    "glympse.com",
    "nintendo.net",
    "cbssports.com",
    "mplxtms.com",
    "recaptcha.net",
    "qlogo.cn",
    "tube8.com",
    "speedtest.net",
    "webtrekk.com",
    "ngoisao.net",
    "juiceadv.com",
    "datropy.com",
    "kinja.com",
    "inc.com",
    "office.net",
    "everestads.net",
    "securespy.net",
    "optorb.com",
    "google.dz",
    "mobify.com",
    "sony.net",
    "intellicast.com",
    "sbnation.com",
    "sourceforge.net",
    "stackexchange.com",
    "thehill.com",
    "mindspark.com",
    "telecomitalia.it",
    "iobit.com",
    "slimspots.com",
    "haberler.com",
    "espncms.com",
    "newyorker.com",
    "myinfotopia.com",
    "adsrv247.com",
    "rtalabel.org",
    "espnfc.com",
    "solvemedia.com",
    "espncareers.com",
    "fcc.gov",
    "3lift.com",
    "neodatagroup.com",
    "sitebeacon.co",
    "snapwidget.com",
    "timeinc.com",
    "pardot.com",
    "admarketplace.net",
    "usmagazine.com",
    "admeld.com",
    "pcfaster.com",
    "adinterax.com",
    "adlure.net",
    "mqcdn.com",
    "gm.com",
    "itim.vn",
    "loading-delivery1.com",
    "usabilla.com",
    "janrainbackplane.com",
    "nbcsports.com",
    "chatango.com",
    "affec.tv",
    "tlvmedia.com",
    "integral.com",
    "wealthfront.com",
    "dsrlte.com",
    "kohls.com",
    "belkin.com",
    "rdrtr.com",
    "careerbuilder.com",
    "leagueoflegends.com",
    "eamobile.com",
    "circularhub.com",
    "linksynergy.com",
    "irs01.com",
    "bannerflow.com",
    "lifestylejournal.com",
    "dickssportinggoods.com",
    "cnnexpansion.com",
    "token.ro",
    "bizrate.com",
    "tfbnw.net",
    "etsystatic.com",
    "answcdn.com",
    "cnnimagesource.com",
    "vox-cdn.com",
    "innity.net",
    "nyt.com",
    "powerreviews.com",
    "adfox.vn",
    "cnnchile.com",
    "helpshift.com",
    "parastorage.com",
    "itau.com.br",
    "9gag.com",
    "appsdt.com",
    "netvibes.com",
    "stellaservice.com",
    "afamily.vn",
    "connextra.com",
    "nbcuni.com",
    "4wnet.com",
    "dedicatedmedia.com",
    "no-ip.com",
    "espnmediazone.com",
    "luminate.com",
    "slate.com",
    "openstreetmap.org",
    "lazada.vn",
    "sophosupd.com",
    "free-coupons-codes.com",
    "wfxtriggers.com",
    "grantland.com",
    "struq.com",
    "latinsoulstudio.com",
    "mixplay.tv",
    "lomadee.com",
    "ypcdn.com",
    "alibabagroup.com",
    "target.com",
    "linknavi1.com",
    "anyclip.com",
    "woopra.com",
    "pg.com",
    "kickass.to",
    "scribd.com",
    "aliyun.com",
    "zillow.com",
    "ptp24.com",
    "ybpangea.com",
    "go2speed.org",
    "hgads.com",
    "gameloft.com",
    "wt-data.com",
    "tbccint.com",
    "deadspin.com",
    "googlehosted.com",
    "protrade.com",
    "gammaplatform.com",
    "tradedoubler.com",
    "ebay.it",
    "gfycat.com",
    "goadservices.com",
    "radikal.com.tr",
    "crashplan.com",
    "googlezip.net",
    "embedly.com",
    "tqn.com",
    "m6d.com",
    "thechive.com",
    "rantsports.com",
    "bluestacks.com",
    "kiosked.com",
    "dailyfinance.com",
    "cafepress.com",
    "digitru.st",
    "s-nbcnews.com",
    "redrock-interactive.com",
    "chicagotribune.com",
    "turnerstoreonline.com",
    "boston.com",
    "kotaku.com",
    "cnnnewsource.com",
    "real.com",
    "clickability.com",
    "netdna-ssl.com",
    "comodo.com",
    "google.dk",
    "ehow.com",
    "updaterex.com",
    "mozillamessaging.com",
    "and.co.uk",
    "fastcompany.com",
    "genk.vn",
    "github.io",
    "vineapp.com",
    "securedvisit.com",
    "feedly.com",
    "astpdt.com",
    "allstate.com",
    "wal.co",
    "hurpass.com",
    "squarespace.com",
    "politico.com",
    "peel-prod.com",
    "cleanprint.net",
    "groupme.com",
    "techtudo.com.br",
    "sessionm.com",
    "vzwwo.com",
    "mentad.com",
    "jezebel.com",
    "mercent.com",
    "rovio.com",
    "wixstatic.com",
    "bingj.com",
    "targetix.net",
    "amzn.to",
    "espn.com.br",
    "ign.com",
    "adfox.ru",
    "kelkoo.com",
    "reference.com",
    "runadtag.com",
    "myswitchads.com",
    "fqrouter.com",
    "saymedia.com",
    "xhcdn.com",
    "nymag.com",
    "nba.com",
    "polarmobile.com",
    "snapengage.com",
    "swoop.com",
    "vbulletin.com",
    "leafletjs.com",
    "mlstatic.com",
    "s-microsoft.com",
    "terra.com.br",
    "drudgereport.com",
    "sabah.com.tr",
    "sporx.com",
    "boomtrain.com",
    "ad-maven.com",
    "bloglovin.com",
    "swypeconnect.com",
    "vui.vn",
    "mynet.com",
    "splash-screen.net",
    "more-results.net",
    "tunein.com",
    "google.com.my",
    "proptp.net",
    "uol.com",
    "oppuz.com",
    "castaclip.net",
    "errorception.com",
    "lexity.com",
    "dreamsadnetwork.com",
    "duckduckgo.com",
    "naver.com",
    "adobesc.com",
    "pandasoftware.com",
    "kiloo.com",
    "sunbeltsoftware.com",
    "logentries.com",
    "rtbsrv.com",
    "quantcast.com",
    "providesupport.com",
    "vox.com",
    "emodio.com",
    "advconversion.com",
    "qpic.cn",
    "wellsfargo.com",
    "browser-update.org",
    "zenguard.biz",
    "boostadvtracking.com",
    "samsungcloudsolution.com",
    "shoprunner.com",
    "tinnong247.net",
    "intermarkets.net",
    "worthly.com",
    "mol.im",
    "likes.com",
    "fmpub.net",
    "maxthon.com",
    "edigitalsurvey.com",
    "servingrealads83.com",
    "163.com",
    "jump-time.net",
    "pornmd.com",
    "goal.com",
    "mynet.com.tr",
    "ancestry.com",
    "dermstore.com",
    "easybreathe.com",
    "box.net",
    "mycdn.me",
    "etahub.com",
    "payclick.it",
    "blip.tv",
    "adrsp.net",
    "apigee.net",
    "extensionanalytics.com",
    "sayyac.net",
    "upsight-api.com",
    "centauro.com.br",
    "ebay.co.uk",
    "espn3.com",
    "dellsupportcenter.com",
    "abcnews.com",
    "adsmarket.com",
    "repubblica.it",
    "netflix.net",
    "medleyads.com",
    "richmetrics.com",
    "phonepower.com",
    "picadmedia.com",
    "imgsmail.ru",
    "sonicwall.com",
    "theblaze.com",
    "targetimg3.com",
    "msocdn.com",
    "luyou360.cn",
    "gittigidiyor.net",
    "mlapps.com",
    "dynectmedia6degrees.com",
    "resultspage.com",
    "goodgamestudios.com",
    "reamp.com.br",
    "foxsports.com",
    "burt.io",
    "feiwei.tv",
    "shareth.ru",
    "espnfrontrow.com",
    "ermisvc.com",
    "w3i.com",
    "publichd.eu",
    "exct.net",
    "24hstatic.com",
    "buscape.com",
    "foxnewsinsider.com",
    "viewmixed.com",
    "redtubefiles.com",
    "webssearches.com",
    "yelpcdn.com",
    "adultfriendfinder.com",
    "lavanetwork.net",
    "fb.com",
    "france24.com",
    "rockyou.com",
    "jwplatform.com",
    "customersvc.com",
    "targetimg1.com",
    "extremetube.com",
    "pandasecurity.com",
    "indiatimes.com",
    "venturecapitalnews.us",
    "brand.net",
    "4shared.com",
    "cnt.my",
    "pictela.net",
    "mulctsamsaracorbel.com",
    "ymail.com",
    "learni.st",
    "youronlinechoices.com",
    "tinypic.com",
    "mega.co.nz",
    "bostonglobe.com",
    "naturalon.com",
    "atil.info",
    "lavamobiles.com",
    "hizliresim.com",
    "friendfeed.com",
    "fame10.com",
    "sheknows.com",
    "cootek.com",
    "usekahuna.com",
    "zelfy.com",
    "friv.com",
    "expedia.com",
    "egistec.com",
    "espnscrum.com",
    "jsadapi.com",
    "worldcat.org",
    "clovenetwork.com",
    "mandrillapp.com",
    "microad.jp",
    "allrecipes.com",
    "tuoitre.vn",
    "qhimg.com",
    "catsupagedwelcome.com",
    "realclearpolitics.com",
    "weheartit.com",
    "pub2srv.com",
    "trackerfix.com",
    "apps.fm",
    "rnengage.com",
    "myfitnesspal.com",
    "begun.ru",
    "videologygroup.com",
    "weather.gov",
    "dmtracker.com",
    "ew.com",
    "foxnewsgo.com",
    "emailsrvr.com",
    "washingtontimes.com",
    "bleacherreport.net",
    "box.com",
    "xtify.com",
    "ppjol.com",
    "sweet-page.com",
    "nt.vc",
    "adshostnet.com",
    "alpha00001.com",
    "startappexchange.com",
    "shareasale.com",
    "sexypartners.net",
    "superuser.com",
    "windowssearch.com",
    "torrentsmd.com",
    "astromenda.com",
    "phpbb.com",
    "openxadexchange.com",
    "hubrus.com",
    "threattrack.com",
    "ravenjs.com",
    "shbdn.com",
    "ghostery.com",
    "rottentomatoes.com",
    "uc.cn",
    "comcast.com",
    "voxmedia.com",
    "sony.com",
    "gaytube.com",
    "chaordicsystems.com",
    "answerscloud.com",
    "tru.am",
    "truste-svc.net",
    "apptap.com",
    "wikia-beacon.com",
    "innity.com",
    "yourjavascript.com",
    "ad120m.com",
    "milliyetemlak.com",
    "blizzard.com",
    "cnnmexico.com",
    "acer.com",
    "peel.com",
    "h3q.com",
    "popcash.net",
    "nest.com",
    "bitdefender.com",
    "newsvine.com",
    "yify-torrents.com",
    "porniq.com",
    "umbel.com",
    "wikia.com",
    "viafoura.com",
    "skim.gs",
    "quickbooks.com",
    "likes-media.com",
    "nflcdn.com",
    "baza.vn",
    "sojern.com",
    "cimcontent.net",
    "minireklam.com",
    "prq.to",
    "lifescript.com",
    "reklamz.com",
    "buysub.com",
    "pbwstatic.com",
    "etbxml.com",
    "outfit7.com",
    "rt.com",
    "ig.com.br",
    "servedbyopenx.com",
    "adtechjp.com",
    "cashtrafic.info",
    "gnu.org",
    "mobilecore.com",
    "thepiratebay.se",
    "magnetic.is",
    "estat.com",
    "oasgames.com",
    "viafoura.net",
    "wp.me",
    "lpsnmedia.net",
    "ssuggest.com",
    "plex.tv",
    "gosquared.com",
    "r7.com",
    "yellowpages.com",
    "exacttarget.com",
    "9cache.com",
    "suproo.com",
    "springboardplatform.com",
    "realsimple.com",
    "ebdr2.com",
    "linkhay.com",
    "rollingstone.com",
    "usa.gov",
    "dowjoneson.com",
    "alljoyn.org",
    "parentalcontrolbar.org",
    "mediasoul.net",
    "livestrong.com",
    "instacontent.net",
    "securestudies.com"};

    for (auto s : strs)
    {
        domains_ << QString::fromStdString(s);
    }
}

TestDnsRequest::~TestDnsRequest()
{

}

void TestDnsRequest::test_async()
{
    // run 100 requests async
    QList< QFuture< void > > futures;

    for (int i = 0; i < 100; ++i)
    {
        QFuture<void> future = QtConcurrent::run([=]()
        {
            DnsRequest *request = new DnsRequest(NULL, getRandomDomain());

            connect(
                request, &DnsRequest::finished,
                [request]()
            {
                request->deleteLater();
            });

            QSignalSpy spySignal(request, SIGNAL(finished()));
            request->lookup();

            spySignal.wait(10000);
            QCOMPARE(spySignal.count(), 1);
        });

        futures << future;
    }

    // test delete requests
    for (int i = 0; i < 100; ++i)
    {
        DnsRequest *request = new DnsRequest(NULL, getRandomDomain());
        request->lookup();
        request->deleteLater();
    }

    for (auto it : futures)
    {
        it.waitForFinished();
    }
}

void TestDnsRequest::test_blocked()
{
    DnsRequest *request = new DnsRequest(NULL, "1.2.3.4");
    request->lookupBlocked();
    QCOMPARE(request->isError(), false);
    QCOMPARE(request->ips().count(), 1);
    QCOMPARE(request->ips()[0], "1.2.3.4");
}

void TestDnsRequest::test_incorrect()
{
    DnsRequest *request = new DnsRequest(NULL, "incorrectdomain");
    request->lookupBlocked();
    QCOMPARE(request->isError(), true);
    QCOMPARE(request->ips().count(), 0);

    DnsRequest *request2 = new DnsRequest(NULL, "192.126.1.256");
    request2->lookupBlocked();
    QCOMPARE(request2->isError(), true);
    QCOMPARE(request2->ips().count(), 0);
}

void TestDnsRequest::test_subdomain()
{
    DnsRequest *request = new DnsRequest(NULL, "blog.hubspot.com");
    request->lookupBlocked();
    QCOMPARE(request->isError(), false);
    QVERIFY(request->ips().count() != 0);
}

QString TestDnsRequest::getRandomDomain()
{
    QMutexLocker locker(&mutex_);
    return domains_[generateIntegerRandom(10, domains_.size() - 1)];

}

#ifdef Q_OS_WIN
    __declspec(thread) char _generator_backing_double[sizeof(std::mt19937)];
    __declspec(thread) std::mt19937* _generator_double;
    __declspec(thread) char _generator_backing_int[sizeof(std::mt19937)];
    __declspec(thread) std::mt19937* _generator_int;
#endif


int TestDnsRequest::generateIntegerRandom(const int &min, const int &max)
{
    std::uniform_int_distribution<int> distribution(min, max);

    #ifdef Q_OS_WIN
        static __declspec(thread) bool inited = false;
        if (!inited)
        {
            _generator_int = new(_generator_backing_int) std::mt19937(clock() + std::hash<std::thread::id>()(std::this_thread::get_id()));
            inited = true;
        }
        return distribution(*_generator_int);
    #else
        static thread_local std::mt19937* generator = nullptr;
        if (!generator) generator = new std::mt19937(clock() + std::hash<std::thread::id>()(std::this_thread::get_id()));
        return distribution(*generator);
    #endif
}

