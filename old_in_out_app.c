#include "minishell.h"


int	ft_input(t_token *tokens)
{
	t_token	*current;
	int		fd;
	int		original_stdin;
	pid_t	pid;
	char	*cmd;
	int		status;

	cmd = tokens->data;
	current = tokens;
	while (current && current->data_type != INP_REDIR)
		current = current->next_token;
	if (!current || !current->next_token)
	{
		printf("I need the file name please :)\n");
		return (1);
	}
	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
	{
		perror("dup");
		return (1);
	}
	fd = open(current->next_token->data, O_RDONLY);
	if (fd == -1)
	{
		perror("fd");
		close(original_stdin);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd);
		close(original_stdin);
		return (1);
	}
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
		if (execlp(cmd, cmd, NULL) == -1)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd);
		if (dup2(original_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2");
		}
		close(original_stdin);
	}
	return (0);
}










int	ft_output(t_token *tokens)
{
	t_token	*current;
	int		fd;
	int		original_stdout;
	pid_t	pid;
	char	*cmd;
	int		status;

	current = tokens;
	cmd = tokens->data;
	while (current && current->data_type != OUT_REDIR)
		current = current->next_token;
	if (!current || !current->next_token)
	{
		printf("I need the file name please :)\n");
		return (1);
	}
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	fd = open(current->next_token->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("fd");
		close(original_stdout);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd);
		close(original_stdout);
		return (1);
	}
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
		if (execlp(cmd, cmd, NULL) == -1)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd);
		if (dup2(original_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2");
		}
		close(original_stdout);
	}
	printf("KOULXI HOWA HADAk");
	return (0);
}





















int	ft_append(t_token *tokens)
{
	t_token	*current;
	int		fd;
	int		original_stdout;
	pid_t	pid;
	char	*cmd;
	int		status;

	current = tokens;
	cmd = tokens->data;
	while (current && current->data_type != APPEND)
		current = current->next_token;
	if (!current || !current->next_token)
	{
		printf("I need the file name please :)\n");
		return (1);
	}
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	fd = open(current->next_token->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("fd");
		close(original_stdout);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd);
		close(original_stdout);
		return (1);
	}
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
		if (execlp(cmd, cmd, NULL) == -1)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd);
		if (dup2(original_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2");
		}
		close(original_stdout);
	}
	return (0);
}






