#ifndef		SHELL
#define		SHELL
#define PROMPT "MyPersonalShell$ "
#define OP_NONE	0
#define OP_SEMICOLON	1
#define OP_AND	2
#define OP_OR	3
			/*		THIS IS FOR ALIASES IN THE SHELL, USING SINGLY LINKED LISTS BECAUSE IT IS BETTER	*/
typedef	struct alias{
	char *name;
	char *value;
	struct alias *next;
} alias_t;

alias_t *find_alias(alias_t *alias_list, char *name);
void handle_alias(char *command, alias_t **alias_list);
void save_alias(alias_t **alias_list, char *name, char *value);
void process_commands(char *line, char *prog_name, char **envp, alias_t **alias_list);
char *next_conditional_command(char **line, int *operator);
int process_command(char *command, char *prog_name, char **envp, alias_t **alias_t);
char *next_command(char **line);
void shell_loop(char *prog_name, char **envp, int fd);
char *read_line(void);
int execute_command(char *arg[], char *prog_name, char **envp);
char *find_path(char *command);
void print_env(char **envp);
char *my_getline(int fd);
int parse_command(char *command, char *argv[]);
char *next_directory(char **path);
void handle_exit(char *arg[]);
void handle_setenv(char *argv[], char *prog_name);
void handle_unsetenv(char *argv[], char *prog_name);
void handle_cd(char *argv[], char *prog_name);
void print_aliases(alias_t *alias_list);
char *replace_variables(char *command, int status);
void remove_comment(char *line);
#endif
