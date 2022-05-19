#include "shell_main.h"

/**
 * find_env_value - function returns the value of a var environment variable
 * @env: array containting all environment variables
 * @var: variable name of environment variable (e.g PATH)
 *
 * Return: PATH value, or NULL if it could not be found
 */
char *find_env_value(char **env, char *var)
{
char **var_val, *env_var, *value;
int i;

for (i = 0; env[i]; i++)
{
/* splitting current environment variable to [VAR] [VALUE] */
var_val = strtow(env[i], '=');
env_var = var_val[0];
value = _strdup(var_val[1]);
/* check if current variable is equal to current input */
if (_strcmp(env_var, var))
{
free_array(var_val);
return (value);
}
free_array(var_val);
free(value);
}
return (NULL);
}

/**
 * current_dir - function checks if the current directory is in the PATH
 * @val: string of PATH
 *
 * Return: 1 if true, 0 otherwise
 */
int current_dir(char *val)
{
int i;

if (val[0] == ':' || val[_strlen(val) - 1] == ':')
return (1);
for (i = 0; val[i] && val[i + 1]; i++)
if (val[i] == ':' && val[i + 1] == ':')
return (1);
return (0);
}



/**
 * check_file_withP - function checks if command is in one of the
 * PATH directories
 * @env: environment variable
 * @command: the command
 *
 * Return: full path to command (with PATH directory), or NULL if command does
 * not exist in PATH
 */
char *check_file_withP(char **env, char *command)
{
struct stat st;
char *build_path, *tmp, *str, **pa;
int i;

str = find_env_value(env, "PATH");
if (!str)
return (NULL);
/* if PATH contains ':' somewhere in the string */
if (current_dir(str) && !stat(command, &st) && !access(command, X_OK))
return (str_concat("./", command));
/* seperate path directories */
pa = strtow(str, ':');
for (i = 0; pa[i]; i++)
{
tmp = str_concat(pa[i], "/");
/* create path to command */
build_path = str_concat(tmp, command);
if (stat(build_path, &st) == 0 && access(build_path, X_OK) == 0)
{
free(str);
free_array(pa);
free(tmp);
return (build_path);
}
free(tmp);
free(build_path);
}
free(str);
free_array(pa);
return (NULL);
}
