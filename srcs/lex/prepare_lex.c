#include "../../includes/minishell.h"

t_list *ft_lstnew(t_token *token)
{
    t_list *new = malloc(sizeof(t_list));
    if (new)
    {
        new->next = NULL;
        new->token = token;
    }
    return new;
}

t_token *new_token()
{
	t_token *token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->str = ft_strdup("");
	token->type = T_WORD;
	
	return token;
}

t_data *new_data()
{
    t_data *data;

    data = (t_data *)ft_calloc(1, sizeof(t_data));
    return data;
}

void	token_to_list(t_list **head, t_token **token, int check)
{
	t_list	*new;

	new = ft_lstnew(*token);
	if (!new)
		return ;
	ft_lstadd_back(head, new);
	if (check == 1)
	{
		*token = new_token();
		if (!(*token))
			err_msg("bash");
	}
}