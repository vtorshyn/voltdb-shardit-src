#ifndef VOLTDBAPPLICATION_H
#define VOLTDBAPPLICATION_H
#include <config.h>

#include <Client.h>
#include <ClientConfig.h>

#include <string>

using namespace voltdb;

class VoltdbApplication
{
public:
    VoltdbApplication();
    ~VoltdbApplication();
    bool run(const int& argc, const char **argv);
private:
    bool makeParams(const int & argc, const char **argv);
    bool invokeGetHistoryProc();
    bool invokeAddMessageProc();
private:
    Client m_client;
    std::string m_server;
    std::string m_message;
};

#endif // VOLTDBAPPLICATION_H
