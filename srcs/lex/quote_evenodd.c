/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_evenodd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:30 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/16 23:26:56 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	even_quote(t_data *data, t_token **token, int *i, char quote)
{
	int	quote_flag;
	int	only_quote;

	quote_flag = 0;
	only_quote = 0;
	while (data->input[*i] != quote)
	{
		if (data->input[*i] == '$' && quote == '\"')
			quote_dsign(data, token, i);
		if (data->input[*i] != quote)
		{
			only_quote++;
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
		}
		if (data->input[*i + 1] == quote)
			quote_flag = 1;
	}
	if (only_quote > 0 && quote_flag == 0 && \
	((data->input[(*i - 1)] == quote && data->input[*i]) == quote))
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
		(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
	}	
}
