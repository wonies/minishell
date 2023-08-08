#include "../../includes/minishell.h"

void	lexer(t_data *data)
{
	t_token	*token;
	int		i;

	i = -1;
	token = new_token();
	if (!token)
		err_msg("bash:");
	while (data->input[++i])
		input_token(data, &token, &i);
	if (*(token)->str)
		token_to_list(&data->tokens, &token, 0);
}

void	input_token(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == ';')
		++(*i);
	if (data->input[*i] == '<' || data->input[*i] == '>' || data->input[*i] == '|')
	{
		if (*(*token)->str)
			token_to_list(&data->tokens, token, 1);
		tokenization(data, token, i);
	}
	else if (data->input[*i] == ' ' || data->input[*i] == '\t')
	{
		if (*(*token)->str)
			token_to_list(&data->tokens, token, 1);
	}
	else if (data->input[*i] == '\'' || data->input[*i] == '\"')
		tokenization(data, token, i);
	else if (data->input[*i] == '$')
		check_dsign(data, token, i);
	else
		(*token)->str = ft_strncat((*token)->str, &data->input[*i], 1);
}

