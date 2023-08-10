/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:43:34 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/10 22:54:21 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->pre = last;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}

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

// void	ft_lstdelone(t_list *lst)
// {
// 	if (!lst)
// 		return ;
// 	if (lst->token)
// 	{
// 		if (lst->token->str)
// 			free(lst->token->str);
// 		free(lst->token);
// 	}
// 	if (lst->env)
// 		free(lst->env);
// 	free(lst);
// }

// void	ft_lstclear(t_list **lst)
// {
// 	t_list	*temp;

// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	(*lst) = 0;
// }