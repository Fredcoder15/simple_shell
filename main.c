#include <stdio.h>
#include <fcntl.h>
#include "shell.h"
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
/* Entry point of the shell program
*
**/

int main(int argc, char *argv[], char **envp){
	int fd;

	fd = STDIN_FILENO;

	if(argc == 2){
		fd = open(argv[1], O_RDONLY);
		if(fd == -1){
			perror(argv[1]);
			return(1);
		}
	}
	shell_loop(argv[0], envp, fd);
	if(fd == 2){
		close(fd);
	}

	return(0);
}
