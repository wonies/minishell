/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_signcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:18 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 15:43:38 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	check_heredoc(t_data *data, t_token **token, int *i)
{
	if (data->tokens && data->tokens->token->re_type == T_HEREDOC)
	{
		(*token)->str = ft_strncat((*token)->str, "$", 1);
		while (data->input[*i] && data->input[*i] != ' ' && \
		data->input[*i] != '|')
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
		--(*i);
		return (1);
	}
	return (0);
}

bool	check_quote(t_data *data, int *i)
{
	int		quote_close;
	char	quote;

	if (data->input[*i] == '\"')
		quote = '\"';
	else if (data->input[*i] == '\'')
		quote = '\'';
	else
		quote = '\0';
	if (data->input[*i] == '\"' || data->input[*i] == '\'')
	{
		quote_close = find_closing_quote(++(*i), data->input, quote);
		if (quote_close == 0)
		{
			--(*i);
			return (0);
		}
		--(*i);
		--(*i);
		return (1);
	}
	return (0);
}

bool	check_ques(t_data *data, t_token **token, int *i)
{
	char	*itoa;	

	if (data->input[*i] == '?')
	{
		itoa = ft_itoa(data->err_code);
		(*token)->str = ft_strncat((*token)->str, itoa, ft_strlen(itoa));
		free(itoa);
		return (1);
	}
	return (0);
}

bool	check_all(t_data *data, t_token **token, int *i)
{
	if (check_heredoc(data, token, i))
		return (1);
	if (check_quote(data, i))
		return (1);
	if (check_space(data, token, i))
		return (1);
	if (check_ques(data, token, i))
		return (1);
	return (0);
}
