// Jacqueline Giggi
// 10/19/2020
// Operating Systems Fall 2020
// Assignment One

#include<stdio.h> //standard io
#include<sys/wait.h> //for wait call
#include<unistd.h> //for fork call
#include<stdlib.h> //general utilities
// Part A: Working with processes in Linux


//Part 1a: write a program prog that repeatedly creates a sub-process using fork, and waits until it terminates. 
//Each child process prints the child PID (using getpid and exit)
//
//Part 1b: Modify prog so that the child process spawns another program b using execve. Program b immediately exits.

int main(int argc, char* argv[])
{
	int n = atoi(argv[1]);
	//printf("user argument is: %d\n", n);
	
	if (argc < 2 || n < 1 || n > 10)
		printf("Please input a number between 1 and 10!\n");
	
	else
		printf("Input is: %d\n", n);
	
		for(int i = 1; i <= n; i++)
		{
			//while fork values return 0, child processes are running
			if(fork() == 0)
			{
				//show child & parent process information
				printf("Child %d running... Child PID: %d, Parent PID: %d.\n", i, getpid(), getppid());
				
				char* argb[] = {"b_run", 0};
				printf("Argument is: %s\n", argb[0]); 
				execv(argb[0], &argb[0]);
				//printf("Argument is: %s", argv[0]);
				printf("Failed to execute program '%s'\n", argb[0]);
				
				//exit
				exit(0);
			}
			else
			{
				//parent process waiting on child to terminate
				wait(NULL);
				printf("Hello from parent: %d!\n", getpid());
			}
		}

	//return 0;
}



//Part 2: Write a program that takes a single int (n) from the command line and create a set of n processes. Each process should display a phrase "I am process x", where x is the process number within n, and then terminates.
//The original parent process should not terminate until all children have terminated 



