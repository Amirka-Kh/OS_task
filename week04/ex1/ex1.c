#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void forkfunction(int n) { 
    
    // process identifier
    pid_t childPID = fork();
    
    // child process returns value zero 
    if (childPID == 0) {
        printf("Hello from child "); 
        printf("[%d - %d]\n", childPID, n );
    }
    // parent process returns value non-zero. 
    else {
        printf("Hello from parent "); 
        printf("[%d - %d]\n", childPID, n);
    }    
} 

int main() 
{ 
    int n;
    scanf("%d", &n);
    forkfunction(n); 
    return 0; 
} 
