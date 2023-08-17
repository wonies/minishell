/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:28:38 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 20:07:11 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnew(void)
{
	t_list	*new_node;

	new_node = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_node)
		err_msg("bash");
	return (new_node);
}

void	env_init(t_data *data, char **env)
{
	t_list	*new_node;
	int		i;

	i = -1;
	while (env[++i])
	{
		new_node = ft_lstnew();
		if (!new_node)
			err_msg("bash");
		new_node->env = ft_strdup(env[i]);
		if (!new_node->env)
			err_msg("bash");
		ft_lstadd_back(&data->envs, new_node);
	}
}

t_bool	env_remove(t_data *data, char *key)
{
	t_list	*env;

	env = env_search(data, key, TRUE);
	if (!env)
	{
		env = env_search(data, key, FALSE);
		if (!env)
			return (FALSE);
	}
	if (!env->pre)
		data->envs = env->next;
	else
		env->pre->next = env->next;
	ft_lstdel(env);
	return (TRUE);
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

t_list	*env_search(t_data *data, char *key, t_bool flag)
{
	char	*env;
	t_list	*cur;
	int		len;

	env = ft_strdup(key);
	if (flag == TRUE)
		env = ft_strncat(env, "=", 1);
	cur = data->envs;
	len = ft_strlen(env);
	while (cur)
	{
		if (!ft_strncmp(cur->env, env, len))
		{
			if (flag == FALSE \
				&& (cur->env[len] != '\0' && cur->env[len] != '='))
				break ;
			free(env);
			return (cur);
		}
		cur = cur->next;
	}
	free(env);
	return (NULL);
}
