#include "../../includes/minishell.h"

void tree_left_right(t_leaf *cur_leaf, t_list *cur_token)
{
    if (cur_token->token->type == T_REDIRECT)
        tree_add_left(cur_leaf, cur_token->token, T_REDIRECT);
    else if (cur_token->token->type == T_CMD)
        tree_add_right(cur_leaf, cur_token->token, T_CMD);
    else if (cur_token->token->type == T_ARG)
    {
        if (cur_token->pre && cur_token->pre->token->type == T_REDIRECT)
            tree_add_left(cur_leaf, cur_token->token, T_ARG);
        else if (cur_token->pre && cur_token->pre->token->type == T_CMD
                 || cur_token->pre && cur_token->pre->token->type == T_ARG)
            tree_add_right(cur_leaf, cur_token->token, T_ARG);
    }
}

t_bool tree_add_left(t_leaf *parent, t_token *new_token, int leaf_type)
{
    t_leaf *child;

    if (!parent || !new_token)
        return (FALSE);
    while (parent->left_child)
        parent = parent->left_child;
    child = create_leaf(leaf_type, parent);
    child->token = new_token;
    parent->left_child = child;
    return (TRUE);
}

t_bool tree_add_right(t_leaf *parent, t_token *new_token, int leaf_type)
{
    t_leaf *child;

    if (!parent || !new_token)
        return (FALSE);
    while (parent->right_child)
        parent = parent->right_child;
    child = create_leaf(leaf_type, parent);
    child->token = new_token;
    parent->right_child = child;
    return (TRUE);
}