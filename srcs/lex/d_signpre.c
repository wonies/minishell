/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_signpre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:36:46 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 14:48:39 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	data_prev(t_data *data, t_token **token)
{
	t_token	*prev;

	prev = ft_lstlast(data->tokens)->token;
	if (prev && prev->type == T_PIPE)
	{
		if (!(*token))
			(*token) = new_token();
		(*token)->str = ft_strncat((*token)->str, "$", 1);
		token_to_list(&data->tokens, token, 1);
		return (1);
	}
	return (0);
}

t_bool	pre_check(t_data *data, t_token **token)
{
	t_token	*prev;

	prev = NULL;
	if (!(data->tokens))
	{
		if (!(*token))
			(*token) = new_token();
		(*token)->str = ft_strncat((*token)->str, "$", 1);
		token_to_list(&data->tokens, token, 1);
		return (1);
	}
	if (data->tokens)
	{
		if (data_prev(data, token))
			return (1);
	}
	return (0);
}

void	inner_space_quo(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '\"')
		double_quotes(data, token, i, 1);
	else
		single_quotes(data, token, i, 1);
}

t_bool	two_space(t_data *data, t_token **token, int *i, int check)
{
	if (!(*token))
		(*token) = new_token();
	(*token)->str = ft_strncat((*token)->str, "$", 1);
	if (check > 0 && data->input[*i] != '\0')
		(*token)->str = ft_strncat((*token)->str, " ", 1);
	while (data->input[*i] != '\0' && data->input[*i] != '|')
	{
		if (data->input[*i] == '\"' || data->input[*i] == '\'')
		{
			inner_space_quo(data, token, i);
			return (1);
		}
		else
		{
			check = 0;
			if (data->input[*i] == ' ')
				return (0);
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
		}
	}
	return (0);
}
