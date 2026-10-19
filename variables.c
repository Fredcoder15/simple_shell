#include <string.h>
#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
				/* This is for the replaccement of the $? and $$ characters in echo command to the status and pid integers but as characters before 
				passing to the normal execution machinery	*/

char *replace_variables(char *command, int status){
	char *new_command;
	int pid;
	int new_size;
	char status_str[12];
	char pid_str[20];
	int i;
	int j;
	int k;
			/* This gets pid and cast as an integer before converting to characters and storing them in pid_str array */
	pid = (int) getpid();

			/* Converts the integers to characters and store them in their respective arrays*/
	snprintf(status_str, sizeof(status_str), "%d", status);
	snprintf(pid_str, sizeof(pid_str), "%d", pid);
		
		/* We need to calculate how much memory will be needed for the new_command string we want, hence we need to know the sizes before dynamic allocation */
	new_size = strlen(command) + 1;
	for(i = 0; command[i] != '\0'; i++){	
		if(command[i] == '$' && (command[i + 1] == '?' || command[i + 1] == '$')){
			new_size -= 2;
			if(command[i + 1] == '?'){
				new_size += strlen(status_str);
			}
			else{
				new_size += strlen(pid_str);
			}
		}
		i++;
	}
	
	new_command = malloc(sizeof(char));
	if(new_command == NULL){
		return(NULL);
	}

		/* This is the part for copying the original command into the new_command string right from echo up until $	*/
	i = 0;
	j = 0;
	while(command[i] != '\0'){
		if(command[i] == '$' && command[i + 1] == '?'){
			k = 0;
			/* Copying for previous program status characters */
			while(status_str[k] != '\0'){
				new_command[j] = status_str[k];
				j++;
				k++;
			}
			i += 2;
		}
		else if(command[i] == '$' && command[i + 1] == '$'){
			k = 0;
			/* Copying for the process id of the current shell characters */
			while(pid_str[k] != '\0'){
				new_command[j] = pid_str[k];
				k++;
				j++;
			}
			i +=2;
		}
		else{
			/* Copying every other thing from the beginning	*/
			new_command[j] = command[i];
			i++;
			j++;
		}
	}
	new_command[j] = '\0';
	return(new_command);
}
