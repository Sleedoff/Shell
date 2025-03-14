#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *reading()
{
	char *input_string = NULL;
	size_t len =0;
	getline(&input_string, &len, stdin);
	return input_string;
}

char **parsing_string(char *full_string)
{
	char **arg = malloc(64 * sizeof(char*));
	char *token;
	int position =0;

	token = strtok(full_string, " \t\n\r");
	while(token != NULL)
	{
		arg[position++] = token;
		token = strtok(NULL, " \t\n\r");
	}
	arg[position] = NULL;
	return arg;
}

void exsisting_cmd(char **arg)
{
	pid_t pid = fork();
    if (pid == 0)
    { 
        execvp(arg[0], arg);
        perror("Ошибка запуска");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else
        perror("Ошибка fork");
}


int main()
{
	char *string;
	char *arg;

	while(1)
	{
		printf("$ ");
		string = reading();
		arg = parsing_string(string);

		if (arg[0] != NULL) {
            exsisting_cmd(arg);
        }

        free(string);
        free(arg);
	}
	return 0;
}