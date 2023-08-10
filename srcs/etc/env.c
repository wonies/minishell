/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:28:38 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/10 22:49:21 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_data *data);

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
	add_env(data);
}

void	add_env(t_data *data)
{
	t_list	*new_node;

	new_node = ft_lstnews();
	new_node->env = ft_strdup("?=0");
	ft_lstadd_back(&data->envs, new_node);
}

// void	get_envp(t_data *data)
// {
// 	t_list	*tmp;
// 	char	**str;
// 	int		size;
// 	int		i;

// 	i = -1;
// 	size = ft_lstsize(data->envs);
// 	str = (char **)ft_calloc(size, sizeof(char *));
// 	tmp = data->envs;
// 	while (++i < size)
// 	{
// 		str[i] = tmp->env;
// 		tmp = tmp->next;
// 	}
// }

char	*find_envp(t_data *data, char *key)
{
	t_list	*tmp;

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
