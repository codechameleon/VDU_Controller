#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

/* Shared memory */
extern char buffer[7];
extern int current;

/* mutex */
extern pthread_mutex_t mutex1;

/* Processes input data that consists of text strings, commands,
 * and possibly errors.
 */
void controller(char input[]) {

	
}

/* Returns the next input character form the buffer if the buffer is
 * not empty.
 */
char buffReader() {

	 pthread_mutex_lock( &mutex1 );

	 pthread_mutex_unlock( &mutex1 );
}

/* Executes a command that is given as the paramter. If parameter comm contains
 * string "NEWLN", for example, this fucntion will print the newline character
 * on the screen.
 */
void execComm(char comm []) {
}

/* Displays on the screen text (including error messages) htat is given as the parameter. 
 * Since the VDU can display up to 30 characters per line, the length of the array line
 * should not exceed the maximum. 
 */
void displayText(char line[]) {
}

