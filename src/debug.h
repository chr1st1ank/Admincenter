#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

#include <iostream>
#include <cstdlib>

#define cDEBUG(s) std::cout << s << std::endl

#define cASSERT_UNREACHABLE(s) { \
    std::cout << std::endl \
              << "Assertion failed in " << __FILE__ \
              << " at line " << __LINE__ << ":" << std::endl \
              << "\tThis code was assumed to be unreachable:" << std::endl \
              << "\t" << s \
              << std::endl; \
    exit(-13); \
}

#define cASSERTX(c, s) if(!(c)) { \
    std::cout << std::endl \
              << "Assertion failed in " << __FILE__ \
              << " at line " << __LINE__ << ":" << std::endl \
              << "\t" << s \
              << std::endl; \
    exit(-13); \
}

#define cASSERT(c) cASSERTX((c), "There is no further description of the error.")

#define cON_DEBUG(c) c

#else // #ifdef DEBUG

#define cDEBUG(s) ((void)0)
#define cASSERT_UNREACHABLE(s) ((void)0)
#define cASSERTX(c, s) ((void)0)
#define cASSERT(s) ((void)0)
#define cON_DEBUG(c) ((void)0)

#endif // #ifdef DEBUG
#endif // #ifndef DEBUG_H

