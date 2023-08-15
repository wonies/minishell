/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:27 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 14:30:37 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		free(token);
		token = NULL;
	}
}

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
	if ((!*token->str) && token->type == 0)
		free_token(token);
}

void	input_token(t_data *data, t_token **token, int *i)
{
	if (data->input[*i] == '<' || data->input[*i] == '>' \
	|| data->input[*i] == '|')
	{
		if (*(*token)->str)
			token_to_list(&data->tokens, token, 1);
		tokenization(data, token, i);
	}
	else if (data->input[*i] == ' ' || data->input[*i] == '\t')
	{
		(*token)->space = 1;
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
