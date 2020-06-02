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
f : flag HIGH
z : flag LOW

Thread 2:

Perform the following function periodically (time control by ‘s’). Default to every seconds
Increase the first character of string buffer : e.g. a → b, or A→ B


Instructions:

   1. Create string buffer
   2. Input string
   3. Print out buffer (Optional)
   4. Update time for Thread 2 (Optional)
   5. Set flag to HIGH to begin increment
   6. Set flag to LOW to pause increment (Optional)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//#pragma pack(1)

/*union data
{
   unsigned int changetime : 4;
   int flag;
   int stopprocess;
}; */

//typedef union data data_t;

unsigned int changetime = 1;
int flag = 0, stopprocess = 0;
char *buffer;
pthread_t t1,t2;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *myfunc1(void *ptr) //Thread t1
{
   //data_t structure;
   char input[0];
   unsigned int *newtime = (unsigned int*)malloc(sizeof(unsigned int));
   printf("Please enter a command\n q:Quit current program\n c:Create string buffer\n s:Insert user key in string into buffer\n g:Print string buffer\n t:Change Thread 2 updating time\n f:Flag HIGH\n z:Flag LOW\n");
 
   while(1)
   {

      scanf("%c",input);

      switch(input[0])
      {
         case 'q':
         {
            free(buffer);
            free(newtime);        
            stopprocess = 1;
            break;
         }

         case 'c':
         {
            if (buffer == NULL)
            {
               buffer=(char*)malloc(sizeof(char));
               printf("String buffer created\n");          
            }

            else
            {
               printf("Buffer was created previously\n");
            }
            
            break;
         }

         case 's':
         {
            printf("Please key in a string\n");
            pthread_mutex_lock(&m);
            scanf("%s",buffer);
            pthread_mutex_unlock(&m);
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
            break;
         }

         case 'f':
         {
            pthread_mutex_lock(&m);
            flag = 1;
            pthread_mutex_unlock(&m);
            break;
         }

         case 'z':
         {
            pthread_mutex_lock(&m);
            flag = 0;
            pthread_mutex_unlock(&m);
            break;
         }  
      }
   }
}

void *myfunc2(void *ptr) //Thread t2
{
   while(1)
   {
      pthread_mutex_lock(&m);
      if(flag == 0)
      {
         pthread_mutex_unlock(&m);
         sleep(1);
      }

	   else if(flag == 1)
	   { 
         pthread_mutex_unlock(&m); 
		   if (buffer)
		   {
            pthread_mutex_lock(&m);
			   buffer[0]+=1;
			   printf("%s\n",buffer);
            pthread_mutex_unlock(&m);                               
			   sleep(changetime);                      
		   }
		 
	   }
   }
}

int main()
{
   //data_t structure;
   pthread_create(&t1,NULL,myfunc1,"Thread1");
   pthread_create(&t2,NULL,myfunc2,"Thread2");
   while (stopprocess != 1)
   {

   }
   pthread_cancel(t1);
   pthread_cancel(t2);
   return EXIT_SUCCESS;

}
