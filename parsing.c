#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/* This handles my parsing and tokenizations rather than using strtok from 
string.h header file
**/

			/* Handles the commands parsing	*/
int parse_command(char *command, char *argv[]){
	int i = 0;
	int argc = 0;

	while(command[i] != '\0'){
				/* Finds where arguements begins	*/
		while(command[i] == ' '){
			i++;
		}

				/* If we have reached the end of the string, leave the loop	*/

		if(command[i] == '\0'){
			break;
		}

		argv[argc] = &command[i];
				
				/* Finds the end of the string	*/
		while(command[i] != ' ' && command[i] != '\0'){
			i++;
		}
		
				/* Replaces the space with null terminator marking end of one argument */
		if(command[i] == ' '){
			command[i] = '\0';
			i++;
		}
				/* get the arguments into the array	*/
		argc++;

	}
				/* Finally end array with null to mark the end of arguments	*/
	argv[argc] = NULL;
	return(argc);
}

char *next_directory(char **path){
	char *start;
	char *current;
				/* Dereference path to get the address of the path because we want to change its contents so the address is needed	*/
	if(*path == NULL){
		return(NULL);
	}

	start = *path;
	current = start;

				/* Walk through it	*/
	while(*current != '\0' && *current != ':'){
		current++;
	}

	if(*current == ':'){
		*current = '\0';
		*path = current + 1;
	}
	else {
		*path = NULL;	
		}
	
	return(start);
}
