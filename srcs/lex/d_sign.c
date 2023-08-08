/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_sign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:36:46 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/08 22:41:50 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	pre_check(t_data *data, t_token **token)
{
	t_token	*prev;

	prev = NULL;
	if (!(data->tokens))
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

bool	possible_env(t_data *data, t_token **token, char *var)
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
		return (0);
	}
	return (1);
}

char	*possible_env_char(t_data *data, char *var)
{
	char	*temp;
	char	*value;

	temp = find_envp(data, var);
	if (temp != NULL)
	{
		value = ft_strtok(temp, "=");
		value = ft_strtok(NULL, "=");
		printf("value is: %s\n", value);
		return (value);
	}
	return (NULL);
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
