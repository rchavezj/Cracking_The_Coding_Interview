// $Id: debug.h,v 1.7 2016-01-14 16:16:52-08 - - $

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <bitset>
#include <climits>
#include <string>
using namespace std;

// debug -
//    static class for maintaining global debug flags, each indicated
//    by a single character.
// setflags -
//    Takes a string argument, and sets a flag for each char in the
//    string.  As a special case, '@', sets all flags.
// getflag -
//    Used by the DEBUGF macro to check to see if a flag has been set.
//    Not to be called by user code.

class debugflags {
   private:
      using flagset = bitset<UCHAR_MAX + 1>;
      static flagset flags;
   public:
      static void setflags (const string& optflags);
      static bool getflag (char flag);
      static void where (char flag, const char* file, int line,
                         const char* func);
};


// DEBUGF -
//    Macro which expands into trace code.  First argument is a
//    trace flag char, second argument is output code that can
//    be sandwiched between <<.  Beware of operator precedence.
//    Example:
//       DEBUGF ('u', "foo = " << foo);
//    will print two words and a newline if flag 'u' is  on.
//    Traces are preceded by filename, line number, and function.

#ifdef NDEBUG
#define DEBUGF(FLAG,CODE) ;
#define DEBUGS(FLAG,STMT) ;
#else
#define DEBUGF(FLAG,CODE) { \
           if (debugflags::getflag (FLAG)) { \
              debugflags::where (FLAG, __FILE__, __LINE__, __func__); \
              cerr << CODE << endl; \
           } \
        }
#define DEBUGS(FLAG,STMT) { \
           if (debugflags::getflag (FLAG)) { \
              debugflags::where (FLAG, __FILE__, __LINE__, __func__); \
              STMT; \
           } \
        }
#endif

#endif
