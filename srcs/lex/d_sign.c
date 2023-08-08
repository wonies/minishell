#include "../../includes/minishell.h"

bool	pre_check(t_data *data, t_token **token)
{
	t_token *prev;

	prev = NULL;
	if ((!(data->tokens)))
	{
		(*token) = new_token();
		(*token)->str = ft_strncat((*token)->str, "$", 1);
		token_to_list(&data->tokens, token, 1);
		return (1);
	}
	if (data->tokens)
	{
		prev = ft_lstlast(data->tokens)->token;
		if (prev && prev->type == T_PIPE)
		{
			(*token) = new_token();
			(*token)->str = ft_strncat((*token)->str, "$", 1);
			token_to_list(&data->tokens, token, 1);
			return (1);
		}
	}
	return (0);
}

void	not_env(t_data *data, t_token **token, int *i, char *var)
{
	int	var_len;

	var_len = ft_strlen(var);
	if (!(*(*token)->str))
		(*token) = new_token();
	if (data->input[*i] != ' ' || data->input[*i] != '\t')
	{
		(*token)->str = ft_strncat((*token)->str, "$", 1);
		(*i) -= (var_len + 1);
		return ;
	}
	(*token)->str = ft_strncat((*token)->str, "$ ", 2);
	(*token)->str = ft_strncat((*token)->str, var, var_len);
	(*i) -= (var_len + 1);
}

bool    possible_env(t_data *data, t_token **token, char *var)
{
    char	*temp;
	char	*value;

    temp = find_envp(data, var);
    if (temp != NULL)
    {
        if (!(*(*token)->str))
            (*token) = new_token();
        value = ft_strtok(temp, "=");
        value = ft_strtok(NULL, "=");
        (*token)->str = ft_strncat((*token)->str, value, ft_strlen(value));
		// token_to_list(&data->tokens, token, 1);
        return 0;
    }
    return 1;
}

char    *possible_env_char(t_data *data, char *var)
{
    char    *temp;
	char	*value;

    temp = find_envp(data, var);
	printf("temp : %s\n", temp);
    if (temp != NULL)
    {
        value = ft_strtok(temp, "=");
        value = ft_strtok(NULL, "=");
		printf("value is : %s\n", value);
        return (value);
    }
    return NULL;
}

bool	check_heredoc(t_data *data, t_token **token, int *i)
{
	if (data->tokens && data->tokens->token->re_type == T_HEREDOC)
	{
		(*token)->str = ft_strncat((*token)->str, "$", 1);
		--(*i);
		return (1);
	}
	return (0);
}