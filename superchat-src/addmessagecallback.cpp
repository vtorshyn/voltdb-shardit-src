#include "addmessagecallback.h"

AddMessageCallback::AddMessageCallback()
{
}

AddMessageCallback::~AddMessageCallback()
{

}

bool AddMessageCallback::callback(InvocationResponse response) throw (voltdb::Exception)
{
    DBG(response.toString());
    return true;
}
