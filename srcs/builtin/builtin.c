/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:06:43 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:06:45 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin_func(char *name);
int	exec_builtin(int builtnum, t_data *data);

int	check_builtin_func(char *name)
{
	if (!ft_strncmp(name, "cd", 3))
		return (1);
	if (!ft_strncmp(name, "echo", 5))
		return (2);
	if (!ft_strncmp(name, "exit", 5))
		return (3);
	if (!ft_strncmp(name, "pwd", 4))
		return (4);
	if (!ft_strncmp(name, "unset", 6))
		return (5);
	if (!ft_strncmp(name, "export", 7))
		return (6);
	if (!ft_strncmp(name, "env", 4))
		return (7);
	return (0);
}

int	exec_builtin(int builtnum, t_data *data)
{
	if (builtnum == 1)
	{
		if (ft_cd(data) == FALSE)
			return (1);
	}
	if (builtnum == 2)
		ft_echo(data->root->left_child->right_child->right_child);
	if (builtnum == 3)
		ft_exit(data);
	if (builtnum == 4)
		ft_pwd();
	if (builtnum == 5)
		ft_unset(data, data->root);
	if (builtnum == 6)
	{
		if (ft_export(data, data->root->left_child->right_child) == FALSE)
			return (1);
	}
	if (builtnum == 7)
	{
		if (ft_env(data) == FALSE)
			return (127);
	}
	return (FALSE);
}
