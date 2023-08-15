/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:28:38 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 14:57:24 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnews(void)
{
	t_list	*new_node;

	new_node = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	return (new_node);
}

void	env_init(t_data *data, char **env)
{
	t_list	*new_node;
	int		i;

	i = -1;
	while (env[++i])
	{
		new_node = ft_lstnews();
		new_node->env = ft_strdup(env[i]);
		ft_lstadd_back(&data->envs, new_node);
	}
}

void	env_remove(t_data *data, char *key)
{
	char	*rem_key;
	t_list	*cur;

	cur = data->tokens;
	rem_key = find_envp(data, key);
	if (rem_key != NULL)
		free(cur->env);
	if (cur->pre->env)
		cur->pre->next = cur->next;
	if (cur->next->env)
		cur->next->pre = cur->pre;
	free(cur);
}

char	*find_envp(t_data *data, char *key)
{
	t_list	*tmp;
	char	*key_equal;

	key_equal = ft_strncat(ft_strdup(key), "=", 1);
	tmp = data->envs;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, key_equal, ft_strlen(key_equal)) == 0)
		{
			free (key_equal);
			return (tmp->env);
		}
		tmp = tmp->next;
	}
	free(key_equal);
	return (NULL);
}
