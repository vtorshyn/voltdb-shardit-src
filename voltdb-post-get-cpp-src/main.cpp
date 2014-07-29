#include <iostream>
#include <voltdbapplication.h>
#include <boost/shared_ptr.hpp>

int main(const int argc, const char ** argv)
{
    boost::shared_ptr <VoltdbApplication> app(new VoltdbApplication);
    app->run(argc, argv);
    return 0;
}

