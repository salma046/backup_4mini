#include "../minishell.h"

void	ft_print(t_node *node, char **cmd, int i)
{
	while (cmd[i])
	{
		write(node->out_file, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(node->out_file, " ", 1);
		i++;
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
			write(node->out_file, "\n", 1);
			return ;
		}
		if (!ft_strcmp(cmd[i], "-n"))
		{
			i++;
			// tmp_tokens = cmd[i]->next_token;
			if (cmd[i] == NULL)
				return ;
			ft_print(node, cmd, i);
		}
		else
		{
			ft_print(node, cmd, i);
			write(node->out_file, "\n", 1);
		}
	}
}
