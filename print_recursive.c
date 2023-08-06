#include "../includes/minishell.h"

void print_tree_recursive(t_leaf *node, int level)

{
    if (!node)
        return;

    for (int i = 0; i < level - 1; i++)
        printf("|     "); // 들여쓰기

    if (level > 0)
        printf("|-- ");

    if (node->token)
    {
        if (node->token->type == T_CMD)
            printf("CMD: %s\n", node->token->str);
        else if (node->token->type == T_ARG)
            printf("ARG: %s\n", node->token->str);
        else if (node->token->type == T_REDIRECT)
        {
            printf("REDIRECT");
            if (node->token->re_type == T_INPUT)
                printf(" (type: <)\n");
            else if (node->token->re_type == T_OUTPUT)
                printf(" (type: >)\n");
            else if (node->token->re_type == T_HEREDOC)
                printf(" (type: <<)\n");
            else if (node->token->re_type == T_APPEND)
                printf(" (type: >>)\n");
        }
    }
    else
    {
        if (node->leaf_type == T_PIPE)
            printf("PIPE\n");
        else if (node->leaf_type == T_CMD)
            printf("CMD\n");
        else if (node->leaf_type == T_ARG)
            printf("ARG\n");
        else if (node->leaf_type == T_REDIRECT)
            printf("REDIRECT\n");
        else
            printf("UNKNOWN\n");
    }

    print_tree_recursive(node->left_child, level + 1);
    print_tree_recursive(node->right_child, level + 1);
}
