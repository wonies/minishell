/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:03:08 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:03:10 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_env_cd(t_data *data, char *key, char *value);

void	ft_update_env_cd(t_data *data, char *key, char *value)
{
	t_list	*tmp;

	if (!key || !value)
		err_msg("bash");
	tmp = env_search(data, key, TRUE);
	if (!tmp)
		ft_add_env_front(data, key, value);
	else
	{
		free(tmp->env);
		tmp->env = ft_strdup(key);
		tmp->env = ft_strncat(tmp->env, "=", 1);
		tmp->env = ft_strncat(tmp->env, value, ft_strlen(value));
		free(key);
		free(value);
	}
}
