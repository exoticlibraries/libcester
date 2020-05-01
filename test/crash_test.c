//!gcc {0} -I. -I../include/ -o out; ./out

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
	pid_t pid1;
	int index = 1;
	pid1 = fork();
	++index;
	if (pid1 == 0) {
		printf("New Process %i\n", pid1);
		++index;
	}	
	printf("Main or New process %i\n", pid1);
	return 0;
}

