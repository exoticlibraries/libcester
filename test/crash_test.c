//!gcc {0} -I. -I../include/ -o out; ./out

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <windows.h>

void cester_run_test(char* test_name) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    HANDLE stdoutPipe_read;
    HANDLE stdoutPipe_write;
    CreatePipe(&stdoutPipe_read, &stdoutPipe_write, &sa, 0);

    STARTUPINFO si = {
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_USESTDHANDLES,
        .hStdOutput = stdoutPipe_write
    };

    PROCESS_INFORMATION pi = {0};

    CHAR command[505];
    snprintf(command, 505, "%s --cester-test=%s  --cester-singleoutput", "C:/Users/azeez/Documents/OPEN_SOURCE/EXOTICLIBRARIES/libcester/test/test_segfault.exe", test_name);
    printf("'%s'\n", command);

    CreateProcess(
        NULL,
        command,
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi);

    CloseHandle(stdoutPipe_write);

    DWORD len;
    DWORD maxlen = 700;
    CHAR buffer[700];

    do {
        ReadFile(stdoutPipe_read, buffer, maxlen, &len, NULL);
        buffer[len] = '\0';
        printf("%s", buffer);
    } while (len > 0);

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD status;
    GetExitCodeProcess(pi.hProcess, &status);

    int last_status = (status & 0x80000000) ? 3 : status;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    printf("\nWe are done: %d-%d\n", last_status, (status & 0x80000000));
}

int main(int argc, char** argv) 
{ 
    cester_run_test("segfault_test_null_ptr");
    cester_run_test("this_should_notbe_affected");
    
    return 0; 
} 