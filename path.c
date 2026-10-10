#include "shell.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* finds if command exist as a file on the harddisk or not	*/

char *find_path(char *command){
	char *directory;
	char *full_path;
	char *path;
	char *path_copy;

			/* check if command already exist and is executable	*/
	
	if(strchr(command, '/') == 0){
		if(access(command, X_OK) == 0){
			return(strdup(command));
		}
	}

			/* else tokenize	*/

	path = getenv("PATH");
	if(path == NULL){
		return(NULL);
	}

	path_copy = strdup(path);	/* copying the path because we donot want to do  odification directly on the original path, on which was not even ours to begin with	*/
	if(path_copy == NULL){
		return(NULL);
	}

	directory = next_directory(&path_copy);

	while(directory != NULL){
		full_path = malloc(strlen(directory) + strlen(command) + 2);	/* 2 accounting for / and a null terminator	*/
		if(full_path == NULL){
			return(NULL);
		}
		
		sprintf(full_path, "%s/%s", directory, command);
		if(access(full_path, X_OK) == 0){
			return(full_path);
		}
		free(full_path);
		
		directory = next_directory(&path_copy);
	}
	return(NULL);
}

