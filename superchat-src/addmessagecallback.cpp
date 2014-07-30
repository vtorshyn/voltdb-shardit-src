#include "addmessagecallback.h"

AddMessageCallback::AddMessageCallback()
{
}

AddMessageCallback::~AddMessageCallback()
{

}

bool AddMessageCallback::callback(InvocationResponse response) throw (voltdb::Exception)
{
    if (!response.success())
    DBG(response.toString());
    return true;
}
