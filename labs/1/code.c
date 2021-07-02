#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// to make fork system call
#include<sys/wait.h>	// to make waitpid system call
#include <string.h>

void  parse(char *input, char **command)
{	
	
     while (*input != '\0') 
     {      
          while (*input == ' ' || *input == '\t' || *input == '\n')
          		{	
               		*input++ = '\0';     
          		}
          *command++ = input;          
          while (*input != '\0' && *input != ' ' && *input != '\t' && *input != '\n') 
          {
          	
               input++;            
          }
     }
     *command = '\0';                
}

int main()
{	
	int status = 0;		// store return 

	char  input[1024];             /* the input input                 */
    char  *command[64];              /* the command input argument      */
    

	while(1)
	{	
		printf("$ ");
		//input[0] = 'a';
		char destination[] = "/bin/";
		
		//scanf("%*c");
		//scanf("%[^\n]", input);	// get a user input
		
		scanf("%[^\n]%*c", input);	// get a user input
		
		//gets(input);
		
		//fgets(input, sizeof(input), stdin);
		
		parse(input, command); 
		
		
		strcat(destination,command[0]);
	

		if( access(destination, F_OK) == 0 )
			{
				
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
						printf("Fork did not work \n");	// print this if fork fails
					}

			}

		else
			{
				printf("This command is not found!! \n");
			}
			
	}

	


	 if (execvp(*command, command) < 0) 
          {    
               printf("ERROR: System call exec failed\n");
          }

	return 0;	// return value ( child process may return this )
}
