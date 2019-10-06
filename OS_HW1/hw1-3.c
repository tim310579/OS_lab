#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	printf("Main Process ID : %d\n\n", getpid());
	pid_t ch1, ch2, ch3, ch4, ch5;

	ch1 = fork();	//produce 1st copy
	if(ch1 == 0){	//in child1 process, main process don't produce aother process
		printf("Fork 1. I'm the child %d, my parent is %d.\n", getpid(), getppid());	//1st copied process
		ch2 = fork();	//produce 2nd copy
		
	
		if(ch2 == 0){	//in child2 process
			printf("Fork 2. I'm the child %d, my parent is %d.\n", getpid(), getppid());
			ch4 = fork();	//produce 4th
			if(ch4 == 0){	//in child4 process 
				printf("Fork 3. I'm the child %d, my parent is %d.\n", getpid(), getppid());
				exit(0);
			}
			else {
				exit(0);	//end child2
			}	
		}
		
		//else{
		ch3 = fork();	//child3 produced by child1, so in child1's process
		if(ch3 == 0){
			printf("Fork 2. I'm the child %d, my parent is %d.\n", getpid(), getppid());
			ch5 = fork();	//produce 5th
			if(ch5 == 0){
				printf("Fork 3. I'm the child %d, my parent is %d.\n", getpid(), getppid());
				exit(0);
			}
			else {
				exit(0);	//end child5
			}
		}
		//}
		
	}
	wait(NULL);		//main wait for 1
	return 0;
} 
