#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/* Shared memory */
extern char buffer[7];
extern int current;

/* mutex */
extern pthread_mutex_t mutex1;

/* Writes a block of seven characters into the buffer as soon as the 
 * buffer is not empty. 
 */
void bufferWriter(char data[]) {
  printf("%s\n",data);
	//pthread_mutex_lock(&mutex1);

	//pthread_mutex_unlock(&mutex1);
}

/* Reads data from an input file and writes the data into the shared 
 * memory.
 */
void devDriver() {

  char ch;
	char data[7];
	int i = 0;

	/* Opens and reads input file */
	FILE *inFile;
	inFile = fopen ("test.txt","r");

	if (inFile == NULL) {
		printf("File could not be opened\n");
	}

	while ( ! feof(inFile)) {
	  for (i=0; i < 7; i++) {
	    fscanf(inFile,"%c",&ch);
	    data[i] = ch;
	  }
	  bufferWriter(data);
     
	}

}

