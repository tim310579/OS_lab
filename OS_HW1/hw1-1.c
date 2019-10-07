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
#define MAX_LINE 80


int main(void)
{
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/
	
	while(should_run){
		printf("osh>");
		int no_wait = 0;
		char *line = NULL;
		size_t buf_size = MAX_LINE/2+1;
		arg[buf_size] = (char*)malloc(buf_size * sizeof(char));
		getline(&arg[buf_size],&buf_size, stdin);
		if(!strncmp(arg[buf_size], "ps -f &", 7)){
			no_wait = 1;
		}
		if(!strcmp(arg[buf_size], "exit\n")){
			break;
		}
		int choose = 0;
		pid_t pid = fork();
		//printf("%d\n", pid);
		//system("ps");
		//int choose = 0;
		char *argv[] = {"ls", 0};
		char *path;
		int sie = strlen(arg[buf_size]);
		path = malloc(sie);
		if(!strcmp(arg[buf_size], "ls\n")){
			choose = 1;
		}
		if(!strncmp(arg[buf_size], "ls ", 3)){
			choose = 1;
		}
		else if(!strncmp(arg[buf_size], "cat ", 4)){
			choose = 2;
	        	strncpy(path, arg[buf_size]+4, sie-5);
		}
		char *argv2[] = {"/bin/cat", path, NULL};
		
		
	if(pid == 0){
		if(choose == 1){
			execvp(argv[0], argv);
		}
		else if(choose == 2){	//cat cmd
			//cat(arg[buf_size]);	
			execvp("/bin/cat", argv2);
		}
		
		else if(!strncmp(arg[buf_size], "date", 4)){
			char *dat[] = {"date", NULL};
			execvp("date", dat);
		}
		else if(!strncmp(arg[buf_size], "ps -f &", 7)){
			no_wait = 1;
			//pid_t yui = fork();
			char *par[] = {"ps", "-f", NULL};
			execvp(par[0],par); 
			//system("ps -f &");
			//exit(0);
			//dup2
			//return -1;
			//sleep(3000);
		}
		else if(!strncmp(arg[buf_size], "ps -f", 5)){
			char *argvps_f[] = {"ps", "-f", NULL};
			execvp("ps", argvps_f);
		}
		else if(!strncmp(arg[buf_size], "ps -ael", 7)){
			char *ael[] = {"ps", "-ael", NULL};
			execvp("ps", ael);
			//system("ps -ael");
		}
		else if(!strncmp(arg[buf_size], "ps", 2)){
			char *argvps[] = {"ps", NULL};
			execvp("ps", argvps);
			//system("ps");
		}
		//else if(!strncmp(arg[buf_size], "exit", 4)){
			
			int y = getppid();
		//	char uu[5];
		//	sprintf(uu, "%d", y);
		//	char *cha[] = {"kill", uu, NULL};
		//	execvp("kill", cha);
			
		//}
		//wait(NULL);
	   	exit (0);	
		
		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will not invoke wait()
		*/
	//wait(NULL);

	}
	//free(arg[buf_size]);
	//fflush(stdout);
	if(no_wait == 0){
		//int t = getpid;
		int status;
	       	waitpid(pid, NULL, 0);
		//pid = wait(&status);
		//printf("%d\n", pid);
	//	exit(0);
	}
	else {
		//exit(0);
	}
	free(arg[buf_size]);
	fflush(stdout);
	
	}
	
	return 0;
}

