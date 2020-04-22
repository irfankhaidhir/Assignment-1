#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

unsigned int changetime = 1;
int flag = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *myfunc1(void *ptr)
{
   char input[0],*buffer;
   unsigned int *newtime = (unsigned int*)malloc(sizeof(unsigned int));
   printf("Please enter a command\n q:Quit current program\n c:Create string buffer\n s:Insert user key in string into buffer\n g:Print string buffer\n t:Change Thread 2 updating time\n");
   while(1)
   {

   scanf("%c",input);

   switch(input[0])
   {
      case 'q':
      return EXIT_SUCCESS;
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
         pthread_mutex_lock(&m);
         changetime = *newtime;
         pthread_mutex_unlock(&m);
         break;
      }

      case 'f':
      {       
         flag = 0;
         break;
      }

   }
   }
}

void *myfunc2(void *ptr)
{
   char string = 'a';
   pthread_mutex_lock(&m);

   while(string != '{')
   {
      if(flag == 0)
      {
         pthread_cond_wait(&cond,&m);  
      }

      else
      {
      
      printf("%c\n",string);
      string+=1;
  
      sleep(changetime);  

      }
 
   }
   pthread_mutex_unlock(&m);     
}

int main()
{
   pthread_t t1,t2;
   pthread_create(&t1,NULL,myfunc1,"Thread1");

   while(1)
   {
      pthread_create(&t2,NULL,myfunc2,"Thread2");
   }
}