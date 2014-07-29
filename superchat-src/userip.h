#ifndef USERIP_H
#define USERIP_H
#include <string>
#include <stdexcept>

class UserIp
{
public:
    UserIp();
    const std::string getIpv4ForIface(std::string iface) throw (std::exception);
    static const std::string getIpv4();
};

#endif // USERIP_H
