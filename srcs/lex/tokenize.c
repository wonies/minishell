#include "../../includes/minishell.h"

void	tokenization(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '|')
		(*token)->type = T_PIPE;
	else if (data->input[*i] == '<' || data->input[*i] == '>')
        redirect_check(data, token, i);
    else if (data->input[*i] == '\'')
        single_quotes(data, token, i, 0);
    else if (data->input[*i] == '\"')
        double_quotes(data, token, i, 0);
    token_to_list(&data->tokens, token, 1);
}

void    redirect_check(t_data *data, t_token **token, int *i)
{
    (*token)->type = T_REDIRECT;
    if (data->input[*i] == '>')
    {
        if (data->input[*i + 1] == data->input[*i])
        {
            (*token)->re_type = T_APPEND;
            (*i)++;
        }
        else
            (*token)->re_type = T_OUTPUT;
    }
    else
    {
        if (data->input[*i + 1] == data->input[*i])
        {
            (*token)->re_type = T_HEREDOC;
            (*i)++;
        }
        else
            (*token)->re_type = T_INPUT;
    }
}
