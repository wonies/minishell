#include "../../includes/minishell.h"

t_leaf	*create_leaf(int leaf_type, t_leaf *parent)
{
	t_leaf	*new_leaf = (t_leaf *)ft_calloc(1, sizeof(t_leaf));
	if (!new_leaf)
		return (NULL);
	new_leaf->parent = parent;
	new_leaf->left_child = NULL;
	new_leaf->right_child = NULL;
	new_leaf->leaf_type = leaf_type;
	return (new_leaf);
}

void	init_leaf(t_data *data)
{
	t_leaf *cur_leaf;
	t_list *cur_token;

	cur_token = data->tokens;
	if (!cur_token)
		return ;
	data->root = create_leaf(T_PIPE, NULL);
	data->root->left_child = create_leaf(T_CMD, data->root);
	cur_leaf = data->root->left_child;
	while (cur_token)
	{
		while (cur_token && cur_token->token->type != T_PIPE)
		{
			tree_left_right(cur_leaf, cur_token);
			cur_token = cur_token->next;
		}
		if (!cur_token)
			break ;
		if (cur_token && cur_token->token->type == T_PIPE)
			create_pipe(&cur_leaf);
		cur_token = cur_token->next;
	}	
}

void	create_pipe(t_leaf **cur)
{
	*cur = (*cur)->parent;
	(*cur)->exist = 1;
	(*cur)->leaf_type = T_PIPE;
	(*cur)->right_child = create_leaf(T_PIPE, *cur);
	*cur = (*cur)->right_child;
	(*cur)->left_child = create_leaf(T_CMD, *cur);
	*cur = (*cur)->left_child;
}
