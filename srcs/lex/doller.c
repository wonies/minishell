#include "../includes/minishell.h"

void	check_dsign(t_data *data, t_token **token, int *i);
bool	check_quote(t_data *data, int *i);
bool	pre_check(t_data *data, t_token **token);
bool	two_space(t_data *data, t_token **token, int *i, int check);
bool	check_space(t_data *data, t_token **token, int *i);
bool	check_heredoc(t_data *data, t_token **token, int *i);
void	not_env(t_data *data, t_token **token, int *i, char *var);


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
			// (*token) = new_token();
			// (*token)->str = ft_strncat((*token)->str, "$", 1);
			// if (check > 0 && data->input[*i] != '\0')
			// 	(*token)->str = ft_strncat((*token)->str, " ", 1);
			// while (data->input[*i] || data->input[*i] == '|')
			// {
			// 	if (data->input[*i] == '\"' || data->input[*i] == '\'')
			// 	{
			// 		if (data->input[*i] == '\"')
			// 			double_quotes(data, token, i, 1);
			// 		else
			// 			single_quotes(data, token, i, 1);
			// 		return 1;
			// 	}
			// 	else
			// 	{
			// 		check = 0;
			// 		(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
			// 	}
			// }
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




		// if ((!(data->tokens)))
		// {
		// 	first_dsign(data, token);
		// 	return (1);
		// }
		// if (data->tokens)
		// 	if (pipe_before_dsign(data, token, prev))
		// 		return (1);







// void	first_dsign(t_data *data, t_token **token)
// {
// 	(*token) = new_token();
// 	(*token)->str = ft_strncat((*token)->str, "$", 1);
// 	token_to_list(&data->tokens, token, 1);
// }

// bool	pipe_before_dsign(t_data *data, t_token **token, t_token *prev)
// {
// 	// t_token	*prev;

// 	prev = ft_lstlast(data->tokens)->token;
// 	if (prev && prev->type =  T_PIPE)
// 	{
// 		(*token) = new_token();
// 		(*token)->str = ft_strncat((*token)->str, "$", 1);
// 		token_to_list(&data->tokens, token, 1);
// 		return (1);
// 	}
// }




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
	if (!var)
		return ;
	if (check_heredoc(data, token, i))
		return ;
	if (check_quote(data, i))
		return ;
	if (check_space(data, token, i))
		return ;
	while (data->input[*i] != '\0' && data->input[*i] != ' ' && data->input[*i] != '\t' \
	&& data->input[*i] != '\'' && data->input[*i] != '\"')
	{
        if (ft_isalnum(data->input[*i]) == 0)
        {
            --(*i);
            break ;
        }
		var = ft_strncat(var, &data->input[(*i)++], 1);
	}
	if (possible_env(data, token, i, var))
		not_env(data, token, i, var);
}


bool    possible_env(t_data *data, t_token **token, int *i, char *var)
{
    char *temp;

    printf("char : %s\n", var);
    temp = find_envp(data, var);
    if (temp != NULL)
    {
        if (!(*(*token)->str))
            (*token) = new_token();
        char *value = ft_strtok(temp, "=");
        value = ft_strtok(NULL, "=");
        printf("value : %s\n", value);
        (*token)->str = ft_strncat((*token)->str, value, ft_strlen(value));
        // (*i)+= 1;
        // (*i)+= ft_strlen(var);
        // token_to_list(&data->tokens, token, 0);
        return 0;
    }
    return 1;
}


char    *possible_env_char(t_data *data, t_token **token, int *i, char *var)
{
    char    *temp;

    temp = find_envp(data, var);
    printf("%s\n", temp);
    if (temp != NULL)
    {
        char *value = ft_strtok(temp, "=");
        value = ft_strtok(NULL, "=");
        printf("prove value :: %s\n", value);
        return (value);
    }
    return NULL;
}

