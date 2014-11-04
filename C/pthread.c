#include <pthread.h>
#include <stdio.h>

/*  Compile and link with -pthread 


for example  "gcc -pthread -g -o thread pthread.c "

*/



/* This is our third thread function.  It is like main(), but for a thread */
void *threadFunc(void *arg){
	char *str;
	int i = 0;

	str=(char*)arg;

	while(i < 10 )
	{
		usleep(1);
		printf("threadFunc says: %s\n",str);
		++i;
	}

	return NULL;
}

void printer(){

int z ;
printf("This function will increment an integer") ;

while(++z < 10000000);

printf("done, z equals %d", z );
}





/* this function is run by the second thread */
void *inc_x(void *x_void_ptr){

	/* increment x to 100 */
	int *x_ptr = (int *)x_void_ptr;
	while(++(*x_ptr) < 100);

	printf("x increment finished\n");

	/* the function must return something - NULL will do */
	return NULL;

}

int main(){

	int x = 0, y = 0;

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y);

	/* this variable is our reference to the second thread */
	pthread_t inc_x_thread;

	/* create a second thread which executes inc_x(&x) */
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x) != 0) {  /*passes the new tread the reference to the thread, 

       int pthread_create(   pthread_t *thread,   const pthread_attr_t *attr,     void *(*start_routine) (void *),     void *arg);
 */
		fprintf(stderr, "Error creating thread \n");
		return 1;
	}
	
	printf("the second thread has incremented x"); 

	/* increment y to 100 in the first thread */
	while(++y < 100);
	printf("y increment finished\n");
	/* wait for the second thread to finish */
	if(pthread_join(inc_x_thread, NULL) != 0) {  //this is waiting for the other thread to return null
		fprintf(stderr, "Error joining thread \n");
		return 2;
	}

	/* show the results - x is now 100 thanks to the second thread */
	printf("x: %d, y: %d\n", x, y);


	/* this is our third thread */
		
	pthread_t pth;	// this is our thread identifier
	int i = 0;  //integer
	/* Create worker thread */
	pthread_create(&pth,NULL,threadFunc,"processing...");  
	/* wait for our thread to finish before continuing */
	pthread_join(pth, NULL /* void ** return value could go here */);

	while(i < 10 ){
		usleep(1);
		printf("third is running... step %d \n" , i);
		++i;
	}


	pthread_t pto;
	pthread_create(&pth,NULL,printer,"processing...");  











	return 0;

}


/* another example    */



int mainTwo(void){
	pthread_t pth;	// this is our thread identifier
	int i = 0;
	/* Create worker thread */
	pthread_create(&pth,NULL,threadFunc,"processing...");
	/* wait for our thread to finish before continuing */
	pthread_join(pth, NULL /* void ** return value could go here */);

	while(i < 10 )
	{
		usleep(1);
		printf("main() is running...\n");
		++i;
	}

	return 0;
}


