#include "gethistorycallback.h"

#include <vector>
#include <iostream>

#include <Table.h>
#include <TableIterator.h>
#include <Row.hpp>

GetHistoryCallback::GetHistoryCallback()
{
}

GetHistoryCallback::~GetHistoryCallback()
{

}

bool GetHistoryCallback::callback(InvocationResponse response) throw (voltdb::Exception)
{
    using namespace std;
    vector <Table> results = response.results();
    DBG(response.toString());
    DBG("The number of Tables: " << results.size());
    for (size_t tables = 0; tables < results.size(); ++tables)
    {
        voltdb::TableIterator iter = results[tables].iterator();
        while (iter.hasNext())
        {
            voltdb::Row row = iter.next();
            OUT(row.getString(2) << ": " << row.getString(3));

        }
    }
    return true;
}
