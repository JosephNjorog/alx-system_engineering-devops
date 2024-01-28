#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int infinite_while(void);

/**
 * main - creates 5 zombie processes
 * Description: create 5 zombie processes in a linux besed system,
 * keep running indefinitely until receiving a signal to terminate
 *
 * Return: always 0 (Success)
 */
int main(void)
{
	pid_t pid;
	short i;

	for (i = 0; i < 5; i++)
	{
		pid = fork();
		if (!pid)
		{
			printf("Zombie process created, PID: %d\n", getpid());
			exit(1);
		}
	}

	return (infinite_while());
}

/**
 * infinite_while - while loop that runs forever
 *
 * Return: 0
 */
int infinite_while(void)
{
	while (1)
		sleep(1);

	return (0);
}
