/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:56:57 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 17:15:12 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			do_cmd(t_data *data);
void			exec_fork(t_data *data);
t_bool			check_dir(char *command);
static t_bool	check_relative_path(char *command);

void	do_cmd(t_data *data)
{
	int		builtnum;
	t_leaf	*temp;

	temp = data->root->left_child->right_child;
	if (data->info->pipe_num >= 300)
	{
		printf("%s\n", E_SYNTAX_PIPE);
		exit(258);
	}
	if (temp != NULL)
		builtnum = check_builtin_func(temp->token->str);
	if (data->root->left_child->left_child != NULL)
		check_redirect (data->root, data);
	if (temp == NULL)
		exit(0);
	if (builtnum != 0)
	{
		exec_builtin(builtnum, data);
		exit(0);
	}
	else
		exec_fork(data);
}

void	exec_fork(t_data *data)
{
	t_pipe	*base;

	base = data->pipe;
	if (!data->root->left_child->right_child)
		return ;
	base->cmd_path = ft_join_cmd(data->root->left_child->right_child);
	if (check_dir(base->cmd_path[0]) == TRUE)
	{
		error_print(base->cmd_path[0], 0, 2);
		exit(126);
	}
	if (check_path(base->cmd_path[0]) == FALSE)
		abs_path(data);
	base->command = set_path(data);
	if (!base->command)
	{
		if (check_relative_path(base->cmd_path[0]) == TRUE)
			error_print(base->cmd_path[0], 0, 1);
		else
			error_print(base->cmd_path[0], 0, 0);
		exit(127);
	}
	execve(base->command, base->cmd_path, data->env_array);
	exit(127);
}

t_bool	check_dir(char *command)
{
	struct stat	path_stat;

	if (check_relative_path(command) == TRUE)
		if (stat(command, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			return (TRUE);
	return (FALSE);
}

static t_bool	check_relative_path(char *command)
{
	if (!ft_strncmp("./", command, 2) || !ft_strncmp("../", command, 3))
		return (TRUE);
	return (FALSE);
}
