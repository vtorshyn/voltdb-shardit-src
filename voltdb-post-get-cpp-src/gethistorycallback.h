#ifndef GETHISTORYCALLBACK_H
#define GETHISTORYCALLBACK_H
#include <config.h>
#include <ProcedureCallback.hpp>
#include <InvocationResponse.hpp>
using namespace voltdb;
class GetHistoryCallback : virtual public ProcedureCallback
{
public:
    GetHistoryCallback();
    virtual bool callback(InvocationResponse response) throw (voltdb::Exception);
    virtual ~GetHistoryCallback();
};

#endif // GETHISTORYCALLBACK_H
