#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// to make fork system call
#include<sys/wait.h>	// to make waitpid system call


int main()
{	
	int status = 0;		// store return 
	char str[100];		// to store user input

	while(1)
	{
		
		scanf("%[^\n]%*c", str);	// get a user input

		pid_t pid = fork(); 	// make a child process

		if(pid > 0) 	// check whether parent process or not
		{  		
			 // parent process should wait continue execution until created child process is completed
			 waitpid(pid, &status, 0);	// suspends execution of the calling process until a child specified by pid argument has changed state
		}

		else if(pid == 0) // check whether child process or not
		{  
			break;	// if child process, then get out of the loop and execute the given command
		}
		else 
		{ 
			printf("Fork did not work");	// print this if fork fails
		}

	}

	system(str);	// execute the command

	
	return 0;	// return value ( child process may return this )
}
