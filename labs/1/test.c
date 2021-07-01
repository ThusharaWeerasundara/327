#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
   
 char *args[]={"rm -r 123",NULL};


   execv("/bin/rm",args);
   printf("Test running");

   return 0;
}