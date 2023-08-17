/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:35 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 13:25:17 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	redirect_check(t_data *data, t_token **token, int *i)
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

void	token_to_list(t_list **head, t_token **token, int check)
{
	t_list	*new;

	new = ft_lstnew_token(*token);
	if ((*token)->str[0] != '\0')
		ft_lstadd_back(head, new);
	else if ((*token)->type != 0)
		ft_lstadd_back(head, new);
	if (check == 1)
	{
		if ((!*(*token)->str) && (*token)->type == 0)
		{
			free(new);
			return ;
		}
		*token = new_token();
		if (!(*token))
			err_msg("bash");
	}
}
