/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:53:54 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 18:55:53 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	syn_cmd(t_list *cur)
{
	if (cur->token && cur->token->type == T_WORD)
		cur->token->type = T_CMD;
	if (cur->token && cur->token->type == T_REDIRECT && !(cur->next))
		return (error_code_read(E_SYNTAX_NEWLINE, 258, 0));
	else if (cur->token && cur->token->type == T_PIPE)
		return (error_code_read(E_SYNTAX_PIPE, 258, 0));
	return (1);
}

void	syn_arg(t_list *cur)
{
	if (cur->pre && cur->pre->pre && cur->pre->pre->token->type == T_REDIRECT \
		&& (cur->pre->token->type == T_ARG))
		cur->token->type = T_CMD;
	else if (cur->pre && (cur->pre->token->type == T_CMD \
		|| cur->pre->token->type == T_ARG || \
	cur->pre->token->type == T_REDIRECT))
		cur->token->type = T_ARG;
	else if (cur->pre && cur->pre->token->type == T_PIPE)
		cur->token->type = T_CMD;
}

t_bool	syn_pipe(t_list *cur)
{
	if (cur->pre && cur->pre->token->type == T_PIPE)
		return (error_code_read(E_SYNTAX_PIPE, 258, 0));
	else if (cur->pre && cur->pre->token->type == T_REDIRECT)
		return (error_code_read(E_SYNTAX_PIPE, 258, 0));
	else if (!cur->next)
		return (error_code_read(E_SYNTAX_PIPE, 258, 0));
	return (1);
}

t_bool	syn_redirect(t_list *cur)
{
	if (cur->pre && cur->pre->token->type == T_REDIRECT)
	{
		if (cur->token->re_type == T_INPUT)
			return (error_code_read(E_SYNTAX_INPUT, 258, 0));
		else if (cur->token->re_type == T_HEREDOC)
			return (error_code_read(E_SYNTAX_HEREDOC, 258, 0));
		else if (cur->token->re_type == T_OUTPUT)
			return (error_code_read(E_SYNTAX_OUTPUT, 258, 0));
		else if (cur->token->re_type == T_APPEND)
			return (error_code_read(E_SYNTAX_APPEND, 258, 0));
	}
	if (!cur->next)
		return (error_code_read(E_SYNTAX_NEWLINE, 258, 0));
	return (1);
}

t_bool	syntax(t_data *data)
{
	t_list	*cur;

	cur = data->tokens;
	if (!cur)
		return (0);
	if (!(syn_cmd(cur)))
		return (0);
	cur = cur->next;
	while (cur)
	{
		if (cur->token->type == T_WORD)
			syn_arg(cur);
		else if (cur->token->type == T_PIPE)
		{
			if (syn_pipe(cur) == 0)
				return (0);
		}
		else if (cur->token->type == T_REDIRECT)
		{
			if (syn_redirect(cur) == 0)
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}
