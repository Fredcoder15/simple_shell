#include "main.h"
#include <stddef.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

/* Handles program execution

**/

int execute_command(char *argv[], char *prog_name, char **envp){
	char *command_path;
	pid_t pid;
	/*	int arg;	*/
	int status;
	/* char *token;	
	int i = 0; 

			tokenization to get the command arguements
	token = strtok(command, " ");
	while(token != NULL && i < 64){		Controls buffer overflow	
		argv[i] = token;
		i++;
		token = strtok(NULL, " ");	 Null because we have to continue splliting from where we stopped	
	}
	argv[i] = NULL; The execve has to know where the arguments end


	argc = parse_command(command, argv);
	(void) argc;	No current need for it but every tokenizer or parse should alwasy know what is has stored	


			Before execution, check if command exist and is executable	*/
	
	command_path = find_path(argv[0]);
	if(command_path == NULL){
		return(127);
	}
			
			/* Begin a fork process, two identical processes; parent and child, containing the exact same amount of code blocks from here onwards	*/
	pid = fork();
	if(pid == -1){
		perror(prog_name);
		return(1);	/* return so that the pid value donot spiral into the else of the second if statement even though they have no connection	*/
	}
	
	if(pid == 0){
		if(execve(command_path, argv, envp) == -1){
			fprintf(stderr, "%s: %s\n", prog_name, strerror(errno));
			exit(127);
		}
	}
	
	waitpid(pid, &status, 0);
	
	if(WIFEXITED(status)){
		return(WEXITSTATUS(status));
	}

	return(1);
}
