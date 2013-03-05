#include "proj2.h"

/* a mutex variable to ensure correct access to shared memory */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

/* Shared memory */
char buffer[7];
int current;


int main() {
	
	int rc1, rc2;
	pthread_t thread1, thread2;
	int i = 0;
	int j = 0;


   /* create two threads, each runing a different function */

   if( (pthread_create( &thread1, NULL, devDriver, &i)))
   {
      printf("Thread creation failed: %d\n", rc1);
   }

   if( (pthread_create( &thread2, NULL, controller, &j)))
   {
      printf("Thread creation failed: %d\n", rc2);
   }

   /* wait till each thread is complete before main continues */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL); 
return 0;

}
