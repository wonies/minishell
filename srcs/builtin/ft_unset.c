/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:03:03 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:03:06 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data, t_leaf *cur_root);
void	update_env_double_char(t_data *data);

void	ft_unset(t_data *data, t_leaf *cur_root)
{
	char	**cmd;
	int		arg_cnt;
	int		i;

	cmd = ft_join_cmd(cur_root->left_child->right_child);
	arg_cnt = ft_cnt_args(cmd);
	i = 1;
	while (i < arg_cnt)
	{
		env_remove(data, cmd[i]);
		++i;
	}
	free_d_char_ptr(cmd);
	update_env_double_char(data);
}

void	update_env_double_char(t_data *data)
{
	free(data->env_array);
	data->env_array = arr_in_env(data);
}
