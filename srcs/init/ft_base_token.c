/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:52:18 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/12 22:27:59 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnew(t_token *token)
{
	t_list	*new;

	new = (t_list *)ft_calloc(1, sizeof(t_list));
	if (new)
	{
		new->next = NULL;
		new->token = token;
	}
	else
		return (NULL);
	return (new);
}

t_token	*new_token(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup("");
	if (!token->str)
		err_msg("not allocated!\n");
	token->type = T_WORD;
	token->sq_print = 0;
	token->dq_print = 0;
	token->space = 0;
	return (token);
}

t_data	*new_data(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	return (data);
}
