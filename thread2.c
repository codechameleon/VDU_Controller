#include "proj2.h"

extern pthread_mutex_t mutex;		
extern pthread_cond_t reading_done;
extern pthread_cond_t writing_done;

extern int  current;			 
extern char buffer[];

// igore the parameter arg which is not useful in this project	

// read seven characters from the input file into an array
// and use bufferWritter() with that array as the parameter
// to store those characters in the buffer shared between 
// threads; do this repeatedly until EOF is reached.  
// note that EOF needs to be stored in the buffer as well. 
void * devDriver(void * arg)
{
 
	char ch;
	char data[6];
	int i = 0;

	/* Opens and reads input file */
	FILE *inFile;
	inFile = fopen ("test.txt","r");

	if (inFile == NULL) {
		printf("File could not be opened\n");
	}
  
	
	while ( ! feof(inFile)) {
	  for (i=0; i &lt; 7; i++) {
	    fscanf(inFile,"%c",&amp;ch);
	    data[i] = ch;
	  
	  }
	   bufferWriter(data);
	}
	
	
	/* Save eof to end */ 
	data[0] = EOF;
	bufferWriter(data);
	    
	
	
    return 0;
	
}

// bufferWriter() stores the seven characters in array data into the  
// shared buffer

void bufferWriter(char data[])
{

   	pthread_mutex_lock(&amp;mutex);
	
	// wait if the current set of characters is finished yet
	if (current &lt; 7) 
		pthread_cond_wait(&amp;reading_done, &amp;mutex);
 	strncpy(buffer, data, 7);
	current = 0;
	
	// signal to reader when the next set of characters is ready
	pthread_cond_signal(&amp;writing_done);

  	pthread_mutex_unlock(&amp;mutex);
}

