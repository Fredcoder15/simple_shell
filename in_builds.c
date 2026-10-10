#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* Handles in-built functions	

**/
					/* Prints the external environment	*/
void print_env(char **envp){
	int j = 0;
	while(envp[j]){
		printf("%s\n", envp[j]);
		j++;
	}
}

					/*handles exit	*/
void handle_exit(char *argv[]){
	int status;
			/*handles just exit alone	*/
	if(argv[1] == NULL){
		exit(0);
	}

	status = atoi(argv[1]);
	exit(status);
}

					/*Handles the setting and deletion of environmental variables */
void handle_setenv(char *argv[], char *prog_name){
	if(argv[1] == NULL || argv[2] == NULL){
		fprintf(stderr, "%s: Usage: Set env variable name\n", prog_name);
		return;
	}
	else{
		if(setenv(argv[1], argv[2], 1) == -1){
			perror(prog_name);
			return;
		}
	}
}

void handle_unsetenv(char *argv[], char *prog_name){
	if(argv[1] == NULL){
		fprintf(stderr, "%s: Usage: Set env variable value\n", prog_name);
		return;
	}
	else{
		if(unsetenv(argv[1]) == -1){
			perror(prog_name);
			return;
		}
	}
}

						/*             Manages directory	*/
void handle_cd(char *argv[], char *prog_name){
	char *directory;
	char *cwd;
	char buffer[1024];

				/*Gets the current working directory from the OS	*/
	cwd = getcwd(buffer, sizeof(buffer));
	if(cwd == NULL){
		perror(prog_name);
		return;
	}

	
				/* Checks for user input	*/
	if(argv[1] == NULL){
		directory = getenv("HOME");
		if(directory == NULL){
			fprintf(stderr, "%s: HOME is not set\n", prog_name);
			return;
		}
	}
	else if(strcmp(argv[1], "-") == 0){
		directory = getenv("OLDPWD");
		if(directory == NULL){
			fprintf(stderr, "%s: cd: %s: No such file or directory\n", prog_name, directory);
			return;
		}
	}
	else{
		directory = argv[1];
	}
					/* Go to destination directory	*/
	if(chdir(directory) == -1){
		fprintf(stderr, "%s: cd: No such file or directory %s\n", prog_name, directory);
		return;
	}
	
	setenv("OLDPWD", cwd, 1);
	cwd = getcwd(buffer, sizeof(buffer));
	if(cwd == NULL){
		perror(prog_name);
		return;
	}
	setenv("PWD", cwd, 1);
}

