/*!gcc {0} -I. -o out.exe; ./out*/

#include <stdio.h>

#ifndef __STDC_VERSION__
    #define __CESTER_INLINE__ 
    #define __CESTER_LONG_LONG__ long
    #define __FUNCTION__ "<unknown>"
#else 
    #define __CESTER_INLINE__ inline
    #define __CESTER_LONG_LONG__ long long
    #define __FUNCTION__ __func__
#endif

int main(int argc, char** argv) {
    printf("%s", __FUNCTION__);
    return 0;
}