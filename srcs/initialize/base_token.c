/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:52:18 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 12:40:01 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnew_token(t_token *token)
{
	t_list	*new;

	new = (t_list *)ft_calloc(1, sizeof(t_list));
	new->next = NULL;
	new->token = token;
	return (new);
}

t_token	*new_token(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->str = ft_strdup("");
	token->type = T_WORD;
	token->blank = 0;
	token->quote = 0;
	return (token);
}

t_data	*new_data(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		err_msg("bash");
	return (data);
}
