#include "voltdbapplication.h"
#include <gethistorycallback.h>
#include <addmessagecallback.h>
#include <userip.h>

#include <cstdlib>
#include <vector>

#include <Procedure.hpp>
#include <Parameter.hpp>
#include <ParameterSet.hpp>
#include <Exception.hpp>

#define HISTORY_ROW_COUNT 5

using std::vector;

VoltdbApplication::VoltdbApplication()
    : m_client(Client::create())
{
}

VoltdbApplication::~VoltdbApplication()
{
}

bool VoltdbApplication::run(const int &argc, const char **argv)
{
    if (!makeParams(argc, argv))
    {
        ERRORMSG("Not enough parameters.");
        OUT("Usage: " << argv[0] << " <serverIp> 'message text'");
        return false;
    }

    OUT("Server: " << m_server);

    if (m_message.size() > 0)
        OUT("Message: " << m_message);

    if (!invokeAddMessageProc())
        return false;
    if (!invokeGetHistoryProc())
        return false;

    return true;
}

bool VoltdbApplication::makeParams(const int &argc, const char **argv)
{
    if (argc < 2)
        return false;
    m_server = argv[1];
    if (argc > 2)
    {
        m_message = argv[2];
    }
    return true;
}

bool VoltdbApplication::invokeAddMessageProc()
{
    if (!m_message.size())
        return true;
    try {
        m_client.createConnection(m_server);
    } catch (voltdb::ConnectException &ex) {
        ERRORMSG("Error: " << ex.what());
        return false;
    }

    std::vector <voltdb::Parameter> parameterTypes(3);
    parameterTypes[0] = voltdb::Parameter(voltdb::WIRE_TYPE_STRING);
    parameterTypes[1] = voltdb::Parameter(voltdb::WIRE_TYPE_STRING);
    parameterTypes[2] = voltdb::Parameter(voltdb::WIRE_TYPE_STRING);

    voltdb::Procedure procedure("AddMessage", parameterTypes);
    voltdb::ParameterSet * params = procedure.params();

    params->addString(std::string(getenv("USER"))).addString(std::string(UserIp::getIpv4())).addString(std::string(m_message));
    boost::shared_ptr<AddMessageCallback> addcallback(new AddMessageCallback());

    m_client.invoke(procedure, addcallback);
    m_client.run();
    return true;
}

bool VoltdbApplication::invokeGetHistoryProc()
{
    try {
        m_client.createConnection(m_server);
    } catch (std::exception &ex) {
        ERRORMSG("Error: " << ex.what());
        return false;
    }
    vector<Parameter> parameterTypes(1);
    parameterTypes[0] = Parameter(voltdb::WIRE_TYPE_SMALLINT);
    //parameterTypes[0] = voltdb::Parameter(voltdb::WIRE_TYPE_STRING);
    Procedure procedure("GetHistory", parameterTypes);

    voltdb::ParameterSet* params = procedure.params();
    try {
        params->addInt16(HISTORY_ROW_COUNT);
        //params->addString("test:)");
    } catch(const std::exception& ex) {
        DBG(ex.what());
        return false;
    }
    boost::shared_ptr<GetHistoryCallback> callback(new GetHistoryCallback());
    m_client.invoke(procedure, callback);
    m_client.run();
    return true;
}
