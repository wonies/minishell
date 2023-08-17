/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:27 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 17:14:01 by donghong         ###   ########.fr       */
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

void	token_check(t_data *data, t_token *token)
{
	if (*(token)->str)
	{
		token->blank = 0;
		token_to_list(&data->tokens, &token, 0);
	}
	if ((!*token->str) && token->type == 0)
		free_token(token);
}

void	lexer(t_data *data)
{
	t_token	*token;
	int		i;
	int		len;

	i = 0;
	token = new_token();
	len = ft_strlen(data->input);
	while (data->input[i])
	{
		if (len <= i)
		{
			if (len < i)
				i = len - 1;
			break ;
		}
		input_token(data, &token, &i);
		++i;
	}
	token_check(data, token);
}

void	blank_check(t_data *data, t_token **token, int *i)
{
	int	blank_i;
	int	flag;

	blank_i = *i;
	flag = 0;
	while (data->input[blank_i])
	{
		if (data->input[blank_i] != ' ')
			flag = 1;
		blank_i++;
	}
	if (flag == 0)
		(*token)->blank = 0;
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
		(*token)->blank = 1;
		blank_check(data, token, i);
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
