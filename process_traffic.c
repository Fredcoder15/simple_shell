#include "main.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int process_command(char *command, char *prog_name, char **envp, alias_t **alias_list)
{
        char *argv[64];
        alias_t *found;
        char *expanded;
        int status;

        if (*command == '\0')
        {
                return (0);
        }

        if (strncmp(command, "alias", 5) == 0 &&
            (command[5] == ' ' || command[5] == '\0'))
        {
                handle_alias(command, alias_list);
                return (0);
        }

        parse_command(command, argv);

        if (argv[0] == NULL)
        {
                return (0);
        }

        if (strcmp(argv[0], "exit") == 0)
        {
                handle_exit(argv);
                return (0);
        }

        if (strcmp(argv[0], "setenv") == 0)
        {
                handle_setenv(argv, prog_name);
                return (0);
        }

        if (strcmp(argv[0], "unsetenv") == 0)
        {
                handle_unsetenv(argv, prog_name);
                return (0);
        }

        if (strcmp(argv[0], "cd") == 0)
        {
                handle_cd(argv, prog_name);
                return (0);
        }

        if (strcmp(argv[0], "env") == 0)
        {
                print_env(envp);
                return (0);
        }

        found = find_alias(*alias_list, argv[0]);

        if (found != NULL)
        {
                expanded = strdup(found->value);

                if (expanded == NULL)
                {
                        return (1);
                }

                status = process_command(expanded, prog_name, envp, alias_list);

                free(expanded);

                return (status);
        }

        return (execute_command(argv, prog_name, envp));
}
