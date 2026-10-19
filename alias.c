#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>
/* This handles alias creation, finding and updating	*/

void save_alias(alias_t **alias_list, char *name, char *value){
	alias_t *new_alias;
	alias_t *current;

	current = find_alias(*alias_list, name);
	if(current != NULL){
		free(current->value);
		current->value = strdup(value);
		return;
	}

	new_alias = malloc(sizeof(alias_t));
	if(new_alias == NULL){
		return;
	}

	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	if(new_alias->name == NULL || new_alias->value == NULL){
		free(new_alias->value);
		free(new_alias->name);
		free(new_alias);
		return;
	}

	new_alias->next = *alias_list;
	*alias_list = new_alias;
}

			
void handle_alias(char *command, alias_t **alias_list){
	char *current;
	char *name;
	char *value;
	alias_t *found;

	current = command;
	while(*current != '\0' && *current != ' '){
		current++;
	}

	if(*current == '\0'){
		print_aliases(*alias_list);
		return;
	}

	current++;
	name = current;
	while(*current != '\0' && *current != '='){
		current++;
	}

	if(*current == '\0'){
		found = find_alias(*alias_list, name);
		if(found != NULL){
			printf("%s = '%s'\n", found->name, found->value);
		}
		return;
	}

	*current = '\0';
	current++;

	if(*current == '\''){
		current++;
	}

	value = current;
	while(*current != '\0' && *current != '\''){
		current++;
	}
	*current = '\0';

	save_alias(alias_list, name, value);		
}

alias_t *find_alias(alias_t *alias_list, char *name){
	while(alias_list != NULL){
		if(strcmp(alias_list->name, name) == 0){
			return(alias_list);
		}
		alias_list = alias_list->next;
	}
	return(NULL);
}


void print_aliases(alias_t *alias_list){
	while(alias_list != NULL){
		printf("%s ='%s'\n", alias_list->name, alias_list->value);
		alias_list = alias_list->next;
	}
}
