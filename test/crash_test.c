//!gcc {0} -I. -I../include/ -o out; ./out

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    wchar_t * test = L"the √. Testing unicode -- English -- Ελληνικά -- Español." ;

    wprintf(L"%s\n", test);
}