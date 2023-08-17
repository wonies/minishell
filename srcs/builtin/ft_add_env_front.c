/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:01:54 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:01:57 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_add_env_front(t_data *head, char *key, char *value);
static t_list	*create_env_node(char *key, char *value);
static void		ft_lstadd_front(t_list **lst, t_list *new);

void	ft_add_env_front(t_data *head, char *key, char *value)
{
	if (head->envs == NULL)
		head->envs = create_env_node(key, value);
	else
		ft_lstadd_front(&(head->envs), create_env_node(key, value));
}

static t_list	*create_env_node(char *key, char *value)
{
	t_list	*new_node;

	new_node = ft_lstnew();
	new_node->token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_node->token)
		err_msg("bash");
	if (value)
	{
		new_node->env = ft_strncat(key, value, ft_strlen(value));
		free(value);
	}
	else
		new_node->env = key;
	return (new_node);
}

static void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	(*lst)->pre = new;
	*lst = new;
}
