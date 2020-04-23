/*

Created by: Irfan
Function: 

Upon process running, create 2 thread, thread function as describe below:

Thread 1:

Accept user command from command prompt
Print out message based on user command prompt
Command supported:
q : Quit current program (whole program)
c : create a string buffer
s : insert user key in string into buffer (created by c)
g : print string buffer (user key in-in string using command s)
t : change thread 2 updating time
f : flag high

Thread 2:

Perform the following function periodically (time control by ‘s’). Default to every seconds
Increase the first character of string buffer : e.g. a → b, or A→ B


Instructions:

   1. Create string buffer
   2. Input string
   3. Print out buffer (Optional)
   4. Update time for Thread 2 (Optional)
   5. Set flag to HIGH to begin increment of string
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

unsigned int changetime = 1;
char *buffer;
int flag = 0;
pthread_t t1,t2;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER, m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *myfunc1(void *ptr)
{
   char input[0];
   unsigned int *newtime = (unsigned int*)malloc(sizeof(unsigned int));
   printf("Please enter a command\n q:Quit current program\n c:Create string buffer\n s:Insert user key in string into buffer\n g:Print string buffer\n t:Change Thread 2 updating time\n f:Set flag to high\n");
   while(1)
   {

   scanf("%c",input);

   switch(input[0])
   {
      case 'q':
      exit(42);
      break;

      case 'c':
      {
         buffer = "New Data";
         printf("String buffer created\n");
         break;

      }

      case 's':
      {
         char string[20];
         printf("Please key in a string not more than 20 words\n");
         scanf("%s",string);
         buffer=string;
         break;

      }

      case 'g':
      printf("%s\n",buffer);
      break;

      case 't':
      {      
         printf("Enter updated time\n");        
         scanf("%u",newtime);
         changetime = *newtime;
         free(newtime);
         break;
      }

      case 'f':
      {
         pthread_mutex_lock(&m1);      
         flag = 1;
         printf("Please wait...\n");
         pthread_mutex_unlock(&m1);
         //sleep(10000);
         break;
      }

   }
   }
}

void *myfunc2(void *ptr)
{
   //char string = 'a';

      if(flag == 0)
      {
         pthread_cond_wait(&cond,&m);  
      }

      else
      {
         pthread_mutex_lock(&m);           
         printf("%s\n",buffer);    
         buffer[0]+=1;                  
         sleep(changetime); 
         pthread_mutex_unlock(&m); 
      }

      //pthread_join(t1,NULL);        
}

int main()
{

   pthread_create(&t1,NULL,myfunc1,"Thread1");  
   while (1)
   {
      pthread_create(&t2,NULL,myfunc2,"Thread2");         
   }

}