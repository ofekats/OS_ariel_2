#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <signal.h>

void handler(int num)
{
	write(STDOUT_FILENO, "\n", 1);
}

int main()
{
	int i;
	char *argv[10];
	char command[1024];
	char *token;
	signal(SIGINT, handler);
	while (1)
	{
		printf("hello: ");
		fgets(command, 1024, stdin);
		command[strlen(command) - 1] = '\0'; // replace \n with \0

		/* parse command line */
		i = 0;
		token = strtok(command, " ");
		while (token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;

		/* Is command empty */
		if (argv[0] == NULL)
			continue;

		/* for commands not part of the shell command language */
		int id = fork();
		if (id < 0)
		{
			perror("Error");
			return 1;
		}
		if (id == 0)
		{
			signal(SIGINT, SIG_DFL); // Reset SIGINT handler to default (ignore)
			int i = 0;
			while (argv[i] != NULL)
			{
				// printf("argv[i] = %s\n", argv[i]);
				// if we have >
				if (strcmp(argv[i], ">") == 0)
				{
					// printf("if >\n");
					char *filename = argv[i + 1];
					int fd1 = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (fd1 < 0)
					{
						perror("Error");
						return 1;
					}
					if (dup2(fd1, 1) < 0)
					{
						perror("Error");
						return 1;
					}
					close(fd1);
					argv[i] = NULL;
					// argv[i+1] = NULL;
					break;
				}
				// if we have >>
				else if (strcmp(argv[i], ">>") == 0)
				{
					// printf("if >>\n");
					char *filename = argv[i + 1];
					int fd1 = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (fd1 < 0)
					{
						perror("Error");
						return 1;
					}
					if (dup2(fd1, 1) < 0) // 1 == stdout
					{
						perror("Error");
						return 1;
					}
					close(fd1);
					argv[i] = NULL;
					// argv[i+1] = NULL;
					// break;
				}
				// if we have |
				else if (strcmp(argv[i], "|") == 0)
				{
					// printf("if |\n");
					// printf("in pipe!\n");
					int fd[2];
					if (pipe(fd) < 0)
					{
						perror("Error");
						return 1;
					}
					int id2 = fork();
					// printf("fork!\n");
					if (id2 < 0)
					{
						perror("Error");
						return 1;
					}
					if (id2 == 0)
					{
						// printf("grandchild!\n");
						close(fd[0]);
						int j = 0;
						// int k = i;
						char *argv1[10];
						while (strcmp(argv[j], "|"))
						{
							// printf("j = %d\n", j);
							argv1[j] = argv[j];
							j++;
						}
						// printf("j = %d\n", j);
						argv1[j] = NULL;
						printf("argv1= %s\n", *argv1);
						// printf("to grandchild: %s\n", **argv1);
						if (dup2(fd[1], 1) < 0) // stdout of grandchild == fd[1] -> write to pipe
						{
							perror("Error");
							return 1;
						}
						execvp(argv1[0], argv1);
					}
					else
					{
						// printf("child!\n");
						int j = 0;
						while (argv[i + 1] != NULL)
						{
							// printf("i= %d\n", i);
							// printf("j= %d\n", j);
							argv[j] = argv[i + 1];
							j++;
							i++;
						}
						argv[j] = NULL;
						printf("to child: %s\n", *argv);
						close(fd[1]);
						if (dup2(fd[0], 0) < 0) // stdin of child == fd[0] -> read of pipe
						{
							perror("Error");
							return 1;
						}

						wait(NULL);
						break;
					}
				}
				// printf("after ifs \n");
				i++;
			}
			// printf("argv= %s\n", *argv);
			execvp(argv[0], argv);
		}
		wait(NULL);
	}
}
