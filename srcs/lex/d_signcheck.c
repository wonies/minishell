#include "../../includes/minishell.h"

bool	check_space(t_data *data, t_token **token, int *i)
{
	int	check;

	check = 0;
	if (data->input[*i] == ' ' || data->input[*i] == '\t')
	{
		if (pre_check(data, token))
			return (1);
		while (data->input[*i] == ' ' || data->input[*i] == '\t')
		{
			++(*i);
			++check;
		}
		if (data->input[*i])
		{
			if (two_space(data, token, i, check))
				return (1);
			--(*i);
		}
		return (1);
	}
	return (0);
}

bool	two_space(t_data *data, t_token **token, int *i, int check)
{
	(*token) = new_token();
	(*token)->str = ft_strncat((*token)->str, "$", 1);
	if (check > 0 && data->input[*i] != '\0')
		(*token)->str = ft_strncat((*token)->str, " ", 1);
	while (data->input[*i] || data->input[*i] == '|')
	{
		if (data->input[*i] == '\"' || data->input[*i] == '\'')
		{
			if (data->input[*i] == '\"')
				double_quotes(data, token, i, 1);
			else
				single_quotes(data, token, i, 1);
			return (1);
		}
		else
		{
			check = 0;
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
		}
	}
	return (0);
}

bool	check_quote(t_data *data, int *i)
{
	if (data->input[*i] == '\"' || data->input[*i] == '\'')
    {
        --(*i);
        return (1);
    }
	return (0);
}


void	check_dsign(t_data *data, t_token **token, int *i)
{
	char	*var;

	++(*i);
	var = ft_strdup("");
	int al_flag;

	al_flag = 0;
	if (!var)
		return ;
	if (check_all(data, token, i))
		return ;
	while (data->input[*i] != '\0' && data->input[*i] != ' ' && data->input[*i] != '\t' \
	&& data->input[*i] != '\'' && data->input[*i] != '\"')
	{
		if (ft_isalnum(data->input[*i]) == 0)
        {
            --(*i);
			al_flag = 114;
            break ;
        }
		var = ft_strncat(var, &data->input[(*i)++], 1);
	}
	if (possible_env(data, token, var))
		not_env(data, token, i, var);
	else
	{
		if (al_flag == 114)
		{
			while (data->input[*i])
				(*token)->str = ft_strncat((*token)->str, &data->input[++(*i)], 1);
		}
		token_to_list(&data->tokens, token, 1);
	}
}

bool	check_all(t_data *data, t_token **token, int *i)
{
	if (check_heredoc(data, token, i))
		return (1);
	if (check_quote(data, i))
		return (1);
	if (check_space(data, token, i))
		return (1);
	return (0);
}
