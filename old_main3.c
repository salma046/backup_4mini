#include "minishell.h"

t_minishell	g_minishell;


int main3(t_minishell data)
{
    t_token *temp_tokens;

    temp_tokens = data.tokens;

    if (ft_check_building(temp_tokens))
    {
		if (!ft_strcmp(temp_tokens->data, "env") && temp_tokens->data)
			ft_env(data);
		if (!ft_strcmp(temp_tokens->data , "unset") && temp_tokens->data)
			ft_unset(NULL,  data);
        check_command(temp_tokens, data.export_env, data.envir);
    }
    else
    {
		printf("\033[32m-->in:%s\033[0\n", temp_tokens->data);
		data.envirement = mk_tenv_char(data.envir);
        int retu = ft_execute(temp_tokens, data.envirement);
		if (retu == 127)
		{
			free_env_array(data.envirement);
			return 1;
		}
		free_env_array(data.envirement);
    }
	printf("\033[36m-->out:%s\033[0m\n", temp_tokens->data);
    return (0);

}