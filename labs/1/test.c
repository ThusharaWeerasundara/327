#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>

int main()
{
    
    char destination[] = "/bin/";
    char command[100];

    scanf("%[^\n]%*c", command);

    strcat(destination,command);

    int fd = access(destination, F_OK);
   
   printf("Test running: %d", fd);

   return 0;
}