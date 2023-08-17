/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:22 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 15:47:59 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstdel(t_list *lst)
{
	if (!lst)
		return ;
	if (lst->token)
	{
		if (lst->token->str)
			free(lst->token->str);
		free(lst->token);
	}
	if (lst->env)
		free(lst->env);
	free(lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdel(*lst);
		*lst = temp;
	}
	(*lst) = 0;
}

void	free_leaf(t_leaf *head)
{
	t_leaf	*temp;

	temp = head;
	if (!temp)
		return ;
	if (temp->left_child)
		free_leaf(temp->left_child);
	if (temp->right_child)
		free_leaf(temp->right_child);
	if (head)
		free(temp);
}
