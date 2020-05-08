/*!gcc {0} -I. -I../include/ -o out.exe; ./out*/

#include <signal.h>
#include <stdio.h>
#include <setjmp.h>

//Declaring global jmp_buf variable to be used by both main and signal handler
jmp_buf buf;


void magic_handler(int s)
{

    switch(s)
    {

        case SIGSEGV:
        printf("\nSegmentation fault signal caught! Attempting recovery..");
        longjmp(buf, 1);
        break;
    }

    printf("\nAfter switch. Won't be reached");

}



int main(void) 
{

    int *p = NULL;

    signal(SIGSEGV, magic_handler);

    if(!setjmp(buf))
    {

         //Trying to dereference a null pointer will cause a segmentation fault, 
         //which is handled by our magic_handler now.
         *p=0xdead;

    }
    else
    {
        printf("\nSuccessfully recovered! Welcome back in main!!\n\n"); 
    }



    return 0;
}