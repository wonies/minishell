/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_leaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:58:26 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 23:22:10 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_tree(t_leaf *cur_leaf, t_list *cur_token)
{
	if (cur_token->token->type == T_REDIRECT)
		left_tree(cur_leaf, cur_token->token, T_REDIRECT);
	else if (cur_token->token->type == T_CMD)
		right_tree(cur_leaf, cur_token->token, T_CMD);
	else if (cur_token->token->type == T_ARG)
	{
		if (cur_token->pre && cur_token->pre->token->type == T_REDIRECT)
			left_tree(cur_leaf, cur_token->token, T_ARG);
		else if ((cur_token->pre && cur_token->pre->token->type == T_CMD) \
			|| (cur_token->pre && cur_token->pre->token->type == T_ARG))
			right_tree(cur_leaf, cur_token->token, T_ARG);
	}
}

t_bool	left_tree(t_leaf *parent, t_token *new_token, int leaf_type)
{
	t_leaf	*child;

	if (!parent || !new_token)
		return (FALSE);
	while (parent->left_child)
		parent = parent->left_child;
	child = create_leaf(leaf_type, parent);
	child->token = new_token;
	parent->left_child = child;
	return (TRUE);
}

t_bool	right_tree(t_leaf *parent, t_token *new_token, int leaf_type)
{
	t_leaf	*child;

	if (!parent || !new_token)
		return (FALSE);
	while (parent->right_child)
		parent = parent->right_child;
	child = create_leaf(leaf_type, parent);
	child->token = new_token;
	parent->right_child = child;
	return (TRUE);
}
