/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:02:16 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:02:19 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_env(t_data *data);

t_bool	ft_env(t_data *data)
{
	char	**cmd;
	int		arg_cnt;

	cmd = ft_join_cmd(data->root->left_child->right_child);
	arg_cnt = ft_cnt_args(cmd);
	if (arg_cnt != 1)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		free_d_char_ptr(cmd);
		return (FALSE);
	}
	free_d_char_ptr(cmd);
	env_print(data);
	return (TRUE);
}
