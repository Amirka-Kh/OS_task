#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[100];
	while(1)
  {
		fgets(str,100,stdin);
    
    // we need args to save commands and their input
		char *args[100];		
		int next=0,i=0,j=0;
    
    // we clear args 
		for(i=0;i<100;i++)
    {
			args[i]=NULL;
		}
    
    // set a new value to i
		i=0;
    
    // alocate memory
		args[0]=(char*)malloc(100);	
    
		while(1)
    {
      // we check if a str have space to separate command and input
			if(str[i]!=' ' && str[i]!='\n' && str[i]!='\0')
      {
				args[next][j]=str[i];
				i++,j++;
			}
      
      // space bar occurs, therefore we switch to next char in str
      // and go to next line (next)
			else if(str[i]==' ')
      {
				i++,j=0,next++;
        // allocate memory for input or command
				args[next]=(char*)malloc(100);
			}
      
      // no input
			else
      {
				break;
			}
		}
		// 0 for child process, works good, no error
    int pid=fork();
		if(pid==0)
    {
      // here we run the process
			execvp(args[0],args,NULL);
		}
	}
	return 0;
}
