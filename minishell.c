#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    t_list *list = NULL;
    t_data *data = NULL;

    data = new_data();
    data->input = readline("bash-3.2.1$ ");
    add_history(data->input);
    env_init(data, env);
    get_envp(data);
    lexer(data);



    syntax(data);
    init_leaf(data);
    print_tree_recursive(data->root, 0);
    
	t_list *cur = data->tokens;
    
	while (cur)
    {
        // printf("env : %s\n", cur->env);
        printf("cur : %d, %d, {%s}, {%p}\n", cur->token->type, cur->token->re_type ,cur->token->str, cur->token);
        cur = cur->next;
    }
}