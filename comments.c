#include "main.h"
#include <stdlib.h>
#include <stdio.h>
/*

Removes the comments before execution with THE MACHINERY	
*/
void remove_comment(char *line){
	int i = 0;
	while(line[i] != '\0'){
		if(line[i] == '#'){
			line[i] = '\0';
			break;
		}
		i++;
	}
}
