#include "../minishell.h"

char    *find_command_path(char *command, char **env){

        char *path_env = NULL;
        char full_path[1024];
        int i = 0, j = 0, k = 0;

        while (env[i] != NULL) 
        {
            if (strncmp(env[i], "PATH=", 5) == 0) {
                path_env = env[i] + 5; 
            }
            i++;
        }
        if (!path_env) {
            errno = ENOENT;
            perror("PATH not found");
            return NULL;
        }
        i = 0;
        while (path_env[i] != '\0') 
        {
            ft_memset(full_path, 0, sizeof(full_path));
            k = 0;

            while (path_env[i] != ':' && path_env[i] != '\0') {
                full_path[k++] = path_env[i++];
            }
            full_path[k++] = '/';
            j = 0;
            while (command[j] != '\0') {
                full_path[k++] = command[j++];
            }
            full_path[k] = '\0';

            if (access(full_path, X_OK) == 0) {
                return ft_strdup(full_path);
            }
            if (path_env[i] == ':')
                i++;
        }
        errno = ENOENT;
    return NULL;
}

void    free_fds(t_minishell data)
{
    int i;

    i = 0;
    if (!data.files)
        return ;
    while (data.files[i])
    {
        close(data.files[i][0]);
        close(data.files[i][1]);
        i++;
    }
    i = 0;
    while (data.files[i])
    {
        free(data.files[i]);
        i++;
    }
    free(data.files);
    data.files = NULL;
}

int ft_execute(t_minishell data, t_node *nodes, char **env) 
{
    char *command_path;
    char **args;
    pid_t pid;

    
    args = nodes->cmd;
    printf("Executing command: %s\n", args[0]);
    command_path = find_command_path(args[0], env);
    if (!command_path) {
		// write(nodes->out_file, args[0], ft_strlen(args[0]));
		// write(nodes->out_file, ": command not found", ft_strlen(": command not found"));
        // write(nodes->out_file, "\n", 1);
		printf("%s: command not found\n", args[0]);
        return 127;
    }

    pid = fork();
    if (pid == -1) {
        perror("Fork");
        free(command_path);
        return -1;
    }
    else if (pid == 0) {
        dup2(nodes->in_file, 1);
	    dup2(nodes->out_file, 0);
	    free_fds(data);
        if (execve(command_path, args, env) == -1) {
            perror("execve");
            free(command_path);
            exit(1);
        }
    } 
    else
    {
        int status;
        waitpid(pid, &status, 0);
        
        if (status >> 8 != 0) {
            perror("Command execution failed");
        }
    }
    free(command_path);
    return 0;
}