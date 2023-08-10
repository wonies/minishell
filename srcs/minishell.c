/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:06:43 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/10 23:24:07 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void leaks()
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    (void)env;
    t_data *data = NULL;
    data = new_data();
    data->input = readline("bash-3.2.1$ ");
    add_history(data->input);
    env_init(data, env);
    // get_envp(data);
    atexit(leaks);
    printf("pointer : %p\n", data->input);
    
    lexer(data);
    syntax(data);
    init_leaf(data);
    print_tree_recursive(data->root, 0);
    free(data->input);

    ft_lstclear(&data->envs);
    // ft_lstclear(&data->tokens);
    free(data);
	// t_list *cur = data->tokens;
    
	// while (cur)
    // {
    //     // printf("env : %s\n", cur->env);
    //     printf("cur : %d, %d, {%s}, {%p}\n", cur->token->type, cur->token->re_type ,cur->token->str, cur->token);
    //     cur = cur->next;
    // }
}
