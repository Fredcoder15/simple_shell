#include "shell.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PROMPT	"MyPersonalShell$ "

/* This controls the shell.  Basically an infinite loop of printing propmpt, 
taking commands 
and executing**/

void shell_loop(char *prog_name, char **envp, int fd){
	char *line;
	alias_t *alias_list = NULL;
	int interactive = isatty(fd);

	while(1){
		if(interactive){
			printf(PROMPT);	/* This (interactive) checks if the shell is connected to a terminal	*/
			fflush(stdout);
		}

				/* Gets command from the input, either from command line or by redirectioning from file. */
		line = my_getline(fd);
		if(line == NULL){
			/*check if shell is still interactive or not	*/
			if(interactive){
				printf("\n");
			}
			/* if it is not interactive, for instance, taking a command from a file by redirectioning or pipes	*/
			break;	/* Leave the infinite loop and starts the shell loop all over, both for interactive and non-interactive cases	*/
		}
	
		
		process_commands(line, prog_name, envp, &alias_list);
		free(line);
	/*	remaining = line;
		while((command = next_command(&remaining)) != NULL){
			process_command(command, prog_name,envp);
			free(line);

		* Exists here because malloc'd lines from get line are only passed as copies to the receiving functions, original copies are still here, when C.P.U returns control, there is a need to free before end of program	*/
	}
}

void process_commands(char *line, char *prog_name, char **envp, alias_t **alias_list){
	char *remaining;
	char *command;
	char *expanded_command;
	int operator;
	int status;
	int should_run;

	remaining = line;
	status = 0;
	should_run = 1;
				/* removes comments before passing line down for execution	*/
	remove_comment(line);

	while((command = next_conditional_command(&remaining, &operator)) != NULL){
		if(should_run){
			expanded_command = replace_variables(command, status);
			if(expanded_command == NULL){
				status = 1;
			}
			else{
			status = process_command(expanded_command, prog_name, envp, alias_list);
			free(expanded_command);
			}
		}

		if(operator == OP_AND){
			should_run = (status == 0);
		}
		else if(operator == OP_OR){
			should_run = (status != 0);
		}
		else {
			should_run = 1;
		}
	}

}
