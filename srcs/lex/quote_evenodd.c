/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_evenodd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:30 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/09 18:53:43 by wonhshin         ###   ########.fr       */
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
		printf("here-----\n");
		if (data->input[*i] == '$' && quote == '\"')
			quote_dsign(data, token, i);
		// if ((data->input[*i] == '\\' && data->input[(*i) + 1] == quote) || \
		// (data->input[*i] == '\\' && data->input[(*i) + 1] == '\\'))
		// 	(*i)++;
		if (data->input[*i] != quote)
		{
			only_quote++;
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
		}
		if (data->input[*i + 1] == quote)
			quote_flag = 1;
	}
	if (only_quote > 0 && quote_flag == 0 && \
	(data->input[*i] == quote && data->input[(*i + 1)] == quote))
	{
		(*i)++;
		printf("check ---- quote !!! \n");
		token_to_list(&data->tokens, token, 0);
	}
}

void	odd_quote(t_data *data, t_token **token, int *i)
{
	while (data->input[*i] != '\"')
	{
		if (data->input[*i] == '$')
			quote_dsign(data, token, i);
		// if ((data->input[*i] == '\\' && data->input[(*i) + 1] == '\"') \
		// || (data->input[*i] == '\\' && data->input[(*i) + 1] == '\\'))
		// 		(*i)++;
		printf("----check----\n");
		(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
		printf("token->str : %s\n", (*token)->str);
	}
}
