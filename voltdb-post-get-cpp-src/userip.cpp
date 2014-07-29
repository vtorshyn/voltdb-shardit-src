#include "userip.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

UserIp::UserIp()
{
}

const std::string UserIp::getIpv4()
{
    UserIp ip_gatherer;
    try {
        return ip_gatherer.getIpv4ForIface("eth0");
    } catch (std::exception &ex) {
        try {
            return ip_gatherer.getIpv4ForIface("wlan0");
        } catch (std::exception & ex) {
            return std::string("Unknown IP");
        }
    }
}

const std::string UserIp::getIpv4ForIface(std::string iface) throw (std::exception)
{
     struct ifaddrs *ifaddr, *ifa;
     int family, status;
     char host[NI_MAXHOST];

     if (getifaddrs(&ifaddr) == -1)
     {
             throw std::runtime_error("The call: getifaddrs failed.");
     }

     for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
     {
             if (ifa->ifa_addr == NULL)
                     continue;

             if ((strcmp(ifa->ifa_name, iface.c_str()) != 0))
             {
                     continue;
             }

             // We have to check for AF_INET
             if (ifa->ifa_addr->sa_family==AF_INET)
             {
                     status = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                     if (0 == status)
                     {
                             freeifaddrs(ifaddr);
                             return host;
                     }
             }
     }
     freeifaddrs(ifaddr);
     throw std::runtime_error("Can't determine user IP");
}
