#include "../minishell.h"

void	ft_print(t_node *node, char **cmd, int i)
{
	(void)node;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	ft_check_n_flag(char **cmd, int *i)
{
	while (cmd[*i] && !ft_strcmp(cmd[*i], "-n"))
	{
		// *flag = 1;
		// *tmp_tokens = (*tmp_tokens)->next_token;
		(*i)++;
	}
	if (!ft_strcmp(cmd[*i - 1], "-n"))
	{
		(*i)--;
	}
}

void	ft_echo(t_node *node,char **cmd)
{
	// t_token	*tmp_tokens;
	int	i;
	// tmp_tokens = data;
	i = 1;
	if (cmd[i])
	{
		if (cmd[i] == NULL)
		{
			write(1, "\n", 1);
			return ;
		}
		ft_check_n_flag(cmd, &i);
		if (!ft_strcmp(cmd[i], "-n"))
		{
			i++;
			if (cmd[i] == NULL)
				return ;
			ft_print(node, cmd, i);
		}
		else
		{
			ft_print(node, cmd, i);
			write(1, "\n", 1);
		}
	}
}
