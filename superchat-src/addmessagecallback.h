#ifndef ADDMESSAGECALLBACK_H
#define ADDMESSAGECALLBACK_H
#include <config.h>
#include <ProcedureCallback.hpp>
#include <InvocationResponse.hpp>

using namespace voltdb;

class AddMessageCallback : public ProcedureCallback
{
public:
    AddMessageCallback();
    virtual bool callback(InvocationResponse response) throw (voltdb::Exception);
    virtual ~AddMessageCallback();
};

#endif // ADDMESSAGECALLBACK_H
