// Jacqueline Giggi
// 10/19/2020
// Operating Systems Fall 2020
// Assignment One

#include<stdio.h> //standard io
#include<sys/wait.h> //for wait call
#include<unistd.h> //for fork call
#include<stdlib.h> //general utilities

int main(int argc, char* argv[])
{
	//convert user input to integer
	int n = atoi(argv[1]);
	//printf("user argument is: %d\n", n);

	//set parameters for user input range
	if (argc < 2 || n < 1 || n > 10)
		printf("Please input a number between 1 and 10!\n");

	else
		printf("Input is: %d\n", n); //test input

		//loop for the number of processes specified by user
		for(int i = 1; i <= n; i++)
		{
			//while fork values return 0, child processes are running
			if(fork() == 0)
			{
				//show child & parent process information
				printf("Child %d running... Child PID: %d, Parent PID: %d.\n", i, getpid(), getppid());

				//run program b (simple print statement & exit)
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
				//show that the parent is the same for all processes
				printf("Hello from parent: %d!\n", getpid());
			}
		}

	//return 0;
}
