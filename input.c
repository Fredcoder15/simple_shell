#include "main.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* Handles interactive and non-interactive input 

**/
#define BUFFER_SIZE 1024

char *my_getline(int fd){
	char *line;
	static char buffer[BUFFER_SIZE];
	static ssize_t size;
	char *new_line;
	static size_t position;
	int i;
	int capacity = 128;

	/* static variables are used here so that they don't get reinitialized on function calls. This is specifically on the event of redirections and piping. Before would need to store command lines each with its own new line and will be extracted indivially with null terminator. On coming back, we need to contiune from where we stopped extraction unlike usual variables	*/
	
	/* Static variables are always initialized automatically with 0	*/

	i = 0;
	line = malloc(capacity);
	while(1){
		if(position >= (size_t) size){
			/* if the position is > 0, means that we have definitely copied some characters from buffer into line, hence we need to refill buffer with new characters of commands if there are still more	*/
			size = read(fd, buffer, BUFFER_SIZE);
			position = 0;
			if(size <= 0){
				/* current size can be zero but we already copied some commands in the last chunked previous interations	*/
				if(i == 0){
					return(NULL);
				}
				line[i] = '\0';
				return(line);
			}
		}
		
			/* copy from buffer using indexing position into line using indexing of i	*/
		line[i] = buffer[position];
		position++;
		i++;

			/* Locate new line characters and replace with null terminators */
		if(line[i - 1] == '\n'){
			line[i - 1] = '\0';
			return(line);	/* This must be here and not outside the if statement, else we would be returning line after single copies of charcters not when we eventually encounter a newline character	*/
		}
			
			/* When line capacity is reached, do reallocation	*/
		if(i + 1 >= capacity){
			capacity *= 2;
			new_line = realloc(line, capacity);
			if(new_line == NULL){
				free(line);
				return(NULL);
			}

			line = new_line;
		}
	}
	return(NULL);
}

			/* This function helps to get individual commands before execution, a semicolon separator	*/
char *next_conditional_command(char **line, int *operator){
	char *start;
	char *current;

	if(*line == NULL){
		return(NULL);
	}

	start = *line;
	current = start;

	while(*current != '\0'){
		if(*current == ';'){
			*current ='\0';
			*line = current + 1;
			*operator = OP_SEMICOLON;
			return(start);
		}

		if(*current == '&' && *(current + 1) == '&'){
			*current = '\0';
			*(current + 1) = '\0';
			*line = current + 2;
			*operator = OP_AND;
			return(start);
		}

		if(*current == '|' && *(current + 1) == '|'){
			*current = '\0';
			*(current + 1) = '\0';
			*line = current + 2;
			*operator = OP_OR;
			return(start);
		}
		current++;
	}
	
	*line = NULL;
	*operator = OP_NONE;
	return(start);
	
}
