#include "../../includes/minishell.h"

void    double_quotes(t_data *data, t_token **token, int *i, int ch)
{
    ++(*i);
	int	end;

	end = find_closing_quote(*i, data->input, '\"');
	if ((*(*token)->str) && ch == 0)
        token_to_list(&data->tokens, token, 1);
	if (end == 0)
	{
		(*token)->str = ft_strncat((*token)->str, &data->input[--(*i)], 1);
		return ;
	}
	else if (end % 2 == 0)
		even_quote(data, token, i, '\"');
	else if (end % 2 != 0)
		odd_quote(data, token, i);
}

void    single_quotes(t_data *data, t_token **token, int *i, int ch)
{
    int	end;

	++(*i);
	end = find_closing_quote(*i, data->input, '\'');
	if ((*(*token)->str) && ch == 0)
        token_to_list(&data->tokens, token, 1);
    if (end == 0)
    {
        (*token)->str = ft_strncat((*token)->str, &data->input[--(*i)], 1);
        return ;
    }
	else if (end % 2 == 0)
		even_quote(data, token, i, '\'');
	else if (end % 2 != 0)
	{
		while (data->input[*i] != '\'')
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
	}
}

void	quote_dsign(t_data *data, t_token **token, int *i)
{
	char	*temp;
	char	*prove_env;
	
	++(*i);
	prove_env = NULL;
	temp = ft_strdup("");
	while (data->input[*i] != ' ' && data->input[*i] != '\t' && data->input[*i] != '\"')
	{
		if (ft_isalnum(data->input[*i]) == 0)
			break ;
		temp = ft_strncat(temp, &data->input[(*i)++], 1);
	}
	prove_env = possible_env_char(data, temp);
	if (prove_env)
		(*token)->str = ft_strncat((*token)->str, prove_env, ft_strlen(prove_env));
	else
		(*i) -= ft_strlen(temp) + 1;
}

int	find_closing_quote(int i, char *line, char quote)
{
	int	cnt;

	cnt = 0;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			++cnt;
		++i;
	}
	if (cnt == 0)
		return (0);
	else
		return (cnt + 1);
	return (-1);
}
