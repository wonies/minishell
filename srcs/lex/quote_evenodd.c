#include "../../includes/minishell.h"

void	even_quote(t_data *data, t_token **token, int *i, char quote)
{
	int	quote_flag;
	
	quote_flag = 0;
	while (data->input[*i] != quote)
	{
		if (data->input[*i] == '$' && quote == '\"')
			quote_dsign(data, token, i);
		if ((data->input[*i] == '\\' && data->input[(*i) + 1] == quote) || data->input[*i] == '\\' && data->input[(*i) + 1] == '\\')
			(*i)++;
		if (data->input[*i] != quote)
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
		if (data->input[*(i + 1)] == quote)
			quote_flag = 1;
	}
	if (quote_flag == 0 && (data->input[*i] == quote && data->input[(*i + 1)] == quote))
	{
		(*i)++;
		token_to_list(&data->tokens, token, 0);
	}
}

void	odd_quote(t_data *data, t_token **token, int *i)
{
	while (data->input[*i] != '\"')
	{
		if (data->input[*i] == '$')
			quote_dsign(data, token, i);
		if ((data->input[*i] == '\\' && data->input[(*i) + 1] == '\"') || data->input[*i] == '\\' && data->input[(*i) + 1] == '\\')
				(*i)++;
		(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
	}
}