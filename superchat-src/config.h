#ifndef CONFIG_H
#define CONFIG_H
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS

#define ERRORMSG(x) std::cout << "Error: " << x << std::endl;
#define OUT(x) std::cout << x << std::endl;
#define DBG(x) std::cout << __PRETTY_FUNCTION__ << ":" << __LINE__ <<" "  << x << std::endl;
//#define DBG(x)

#endif // CONFIG_H
