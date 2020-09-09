#include <stdio.h>
#include <stdlib.h>

/* For 3 fork() executions - 8 processes are created.
The parent creates dublicate of its process. We call this process "child"
There will be 1 child processcreated by the 1st fork()
There will be 2 child processes created by the 2nd fork()
There will be 4 child processes created by the 3rd fork()
this is branch from child process, but we have a parent 
therefore 4*2 = 8 the same logic for 5 */
//0 -- 0 -- 0 -- 0
//     |    |
//     |    0
//     |
//     | -- 0 -- 0
//     |
//     0

//For 5 fork() executions - 32 processes are created.

int main(){
	int i;
	for(i=0;i<5;i++){
		fork();
	}
	sleep(5);
	return 0;
}

/* 
//for 3 fork() executions
int main(){
	int i;
	for(i=0;i<5;i++){
		fork();
	}
	sleep(5);
	return 0;
}
*/
