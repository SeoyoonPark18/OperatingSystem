/* Seoyoon Park Lab1
1. In this program, child pthread is keep repeating in the infinite loop, printing every 3 seconds, until it gets cancelled.
2. The reason why sleeping thread can print its periodic messages is because the thread is just paused for a period of time,
	while the main thread is working separately.
*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
//#include <conio.h> //getch
#define ENTER 13

static void *child(void *ignored) {
	while (1) { //infinite loop
		sleep(3); //wait for 3 seconds
		printf("Child is done sleeping 3 seconds.\n");
	}	
	return NULL;
}

int main(int argc, char *argv[]) {
	
	pthread_t child_thread; //second thread
	int code;
	code = pthread_create(&child_thread, NULL, child, NULL); //create second thread
	if (code) {
		fprintf(stderr, "pthread_create failed with code %d\n", code);
	}

	char c; //needed for enter
	printf("\nPress Enter \n");
	//c = _getch(); //input value


	/*
	if (_kbhit()) { //keyboard input check
		c = _getch(); //get input value
		if (c == ENTER) { //if it's ENTER
			pthread_cancel(child_thread); //kill second thread
			sleep(5); //wait for 5 seconds
			printf("Parent is done sleeping 5 seconds.\n");
		}
	}
	*/

	scanf("%c", &c); //get input value
	if (c == 13) { //if it's ENTER
		pthread_cancel(child_thread); //kill second thread
		sleep(5); //wait for 5 seconds
		printf("Parent is done sleeping 5 seconds.\n");
	}

	
	return 0;
}