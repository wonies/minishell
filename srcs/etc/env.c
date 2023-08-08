/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:28:38 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/08 22:29:50 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnews(void)
{
	t_list	*new;

	new = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	return (new);
}

void	env_init(t_data *data, char **env)
{
	t_list	*new;
	int		i;

	i = -1;
	while (env[++i])
	{
		new = ft_lstnews();
		new->env = ft_strdup(env[i]);
		ft_lstadd_back(&data->envs, new);
	}
}

void    get_envp(t_data *data)
{
    t_list  *tmp;
    char    **str;
    int     size;
    int     i;
    
    i = -1;
    size = ft_lstsize(data->envs);
    str = (char **)ft_calloc(size, sizeof(char *));
    tmp = data->envs;
    while (++i < size)
    {
        str[i] = tmp->env;
        tmp = tmp->next;
    }
}

char    *find_envp(t_data *data, char *key)
{
    t_list *tmp;

    key = ft_strncat(key, "=", 1);
    tmp = data->envs;
    while (tmp)
    {
        if (ft_strncmp(tmp->env, key, ft_strlen(key)) == 0)
            return (tmp->env);
        tmp = tmp->next;
    }
    return (NULL);
}
