#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// to make fork system call
#include<sys/wait.h>	// to make waitpid system call
#include <string.h>

void  parse(char *line, char **argv)
{	
	
     while (*line != '\0') 
     {      
          while (*line == ' ' || *line == '\t' || *line == '\n')
          		{	
               		*line++ = '\0';     
          		}
          *argv++ = line;          
          while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
          {
          	
               line++;            
          }
     }
     *argv = '\0';                
}

int main()
{	
	int status = 0;		// store return 

	char  line[1024];             /* the input line                 */
    char  *argv[64];              /* the command line argument      */
    

	while(1)
	{	
		printf("$ ");
		//line[0] = '\0';
		char destination[] = "/bin/";
		
		scanf("%*c");
		scanf("%[^\n]", line);	// get a user input
		//gets(line);
		//fgets(line, sizeof(line), stdin);
		
		parse(line, argv); 
		
		
		strcat(destination,argv[0]);
	

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

	
	printf("%s \n",*argv);

	 if (execvp(*argv, argv) < 0) 
          {    
               printf("ERROR: System call exec failed\n");
          }

	return 0;	// return value ( child process may return this )
}
