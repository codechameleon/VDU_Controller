#include "proj2.h"

extern pthread_mutex_t mutex;	
extern pthread_cond_t reading_done;
extern pthread_cond_t writing_done;
	
extern int  current;			 
extern char buffer[];



/* Displays on the screen text (including error messages) htat is given as the parameter. 
 * Since the VDU can display up to 30 characters per line, the length of the array line
 * should not exceed the maximum. 
 */
void displayText(char line[]) {
	
    int i = 0;
    for (i = 0; i &lt; 30; i++) {
	printf("%c",line[i]);
    }	
}

/* Executes a command that is given as the paramter. If parameter comm contains
 * string "NEWLN", for example, this fucntion will print the newline character
 * on the screen.
 */
void execComm(char comm []) {
    
    char newline[] = "NEWLN";
    char delay[] = "DELAY";
    char smile[] = "SMLY";
    int value = 1;
    int error = 1;
    
    /* Compare if command is newline */
    value = strcmp(comm,newline);
    if (value == 0) {
	printf("\n");
	error = 0;
    }
    
    /* Compare if command is delay */
    value = strcmp(comm,delay);
    if (value == 0) {
	sleep(1);
	error = 0;
    }
    
    /* Compare if command is tab */
    value = strcmp(comm,smile);
    if (value == 0) {
	printf(":)");
	error = 0;
    }
    
    /* Else command is error */
    if (error == 1) {
	printf("\nError Invalid Command.\n\n");
    }
}


// bufferReader() returns one character from the shared buffer 

char bufferReader()
{
   char ch;
   
   pthread_mutex_lock( &amp;mutex );
	
    // wait if the next set of characters is not ready yet
   if (current == 7) 
	pthread_cond_wait( &amp;writing_done, &amp;mutex );
   ch = buffer[current++];
	
    // signal to writer if the current set of characters is finished  
   if (current == 7)
	pthread_cond_signal(&amp;reading_done);

   pthread_mutex_unlock( &amp;mutex );

   return ch;
}

// igore the parameter arg which is not useful in this project	

// use bufferReader() to receive one character from the buffer
// shared between threads and process it; do this repeatedly
// until EOF is encountered. also define functions displayText() 
// and execComm() to perform the required actions.
void * controller(void * arg)
{
    
    char ch,nxt;
    char cmd[5];
    char line[29];
	
    /* Index of line array */
    int i = 0;
	
    int k = 0;
    int j = 5;
	
    /* Saves the last space of line */
    int s = 0;


	
    /* Get rid of the first whitespace */
    for (i = 0; i&lt;7; i++) {
	ch = bufferReader();
    }

    i=0;
	
    /* Reads all of the text */
    while (ch != EOF) {
	     
	/* If 30 characters are met */
	if (i == 30) {
	    i = 0;
	      
	    /* Check if the next character is a space */
	    nxt = bufferReader();
	      
	    /* If it is a space then the array fits on the line */
	    if (nxt == ' ') {
		displayText(line);
		
	    /* If not then we will print whatever was up to the last space before
	     * and then store the remaining word that was too long into the start of the
	     * array for the next line to print */
	    } else {
		      
		/* copy all of the original text into a temp from the last space */
		char *str = (char *) calloc(s, sizeof(char));
		for (i = 0; i &lt; s; i++) {
		    str[i] = line[i];
		}
		displayText(str);
		free(str);
		i= 0;
		
		/* Gets the remaining text that is too big for the line and set them to 
		 * the beginning of the array 
		 */
		while(s &lt; 29) {
		    s++;
		    char c = line[s];
		    line[i] = c;
		    i++; 
		}
		  
		/* add in the called character to the next spot */
		line[i] = nxt;
		ch = nxt;
		i++;
	    }
	    printf("\n");
	      
	  /* If we are filling up the array to print */
	} else {
	    ch = bufferReader();
	      
	      /* Start command */
	      if (ch == '[') {
		  
		  j = 0;
		  
		  /* Get inside of command statement */
		  while (ch = bufferReader(), ch != ']') {
		      cmd[j] = ch;
		      j++;
		      if (j &gt; 5) {
			  break;
		      }
		  }
		  
		  cmd[j] = '\0';
		  
		  /* copy all of the original text into a temp from the last space */
		  char *te = (char *) calloc(i, sizeof(char));
		  for (k=0; k &lt; i; k++) {
		      te[k] = line[k];
		  }
		  displayText(te);
		  
		  execComm(cmd);
		  free(te);
		  
		  i = 0;
		  printf("\n");
		   k = 0;
		   
	          /* Reset command */
		  for (j=0; j &lt; 6; j++) {
		     cmd[j] = ' ';
		  }
		
	      /* Not a command */
	      } else {
	      
		  /* Skip newline characters */
		  if (ch == '\n') {
		      i--;
		      ch = bufferReader();
	          }
		  line[i] = ch;
	      
	          /* Saves all of the space locations */
	          if (ch == ' ') {
		      s = i;
	          } 
	          i++;
	    
	      }
	  }
   }
   
    /* If there is remaining characters to print then print them */
    char *str = (char *) calloc(s,sizeof(char));
    for (i = 0; i &lt; s; i++) {
	str[i] = line[i];
    }
    displayText(str);
    free(str);
	    
    return 0;
}
