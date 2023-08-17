/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:33:34 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 18:43:34 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**arr_in_env(t_data *data)
{
	t_list	*tmp;
	int		size;
	int		i;
	char	**arr;

	i = -1;
	size = ft_lstsize(data->envs);
	arr = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		err_msg("bash");
	tmp = data->envs;
	while (++i < size)
	{
		arr[i] = tmp->env;
		if (!arr[i])
		{
			while (i--)
				free(arr[i]);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (arr);
}

void	env_print(t_data *data)
{
	t_list	*cur;

	cur = data->envs;
	while (cur)
	{
		printf("%s\n", cur->env);
		cur = cur->next;
	}
}
