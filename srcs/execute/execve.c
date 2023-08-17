/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:57:30 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 20:15:12 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		execute(t_data *data);
void		execute_cmd(t_data *data, int flag);
static void	execute_single_cmd(t_data *data, t_pipe *base, int i, int flag);

void	execute(t_data *data)
{
	count_pipe(data);
	heredoc_flag(data->root, data);
	data->info->heredoc_file = \
		(char **)ft_calloc(data->info->heredoc_flag + 1, sizeof(char *));
	if (!data->info->heredoc_file)
		err_msg("bash");
	if (!data->info->pipe_num && !data->info->heredoc_flag)
		if (check_builtin(data) == TRUE)
			return ;
	if (data->info->heredoc_flag)
	{
		if (fork_heredoc (data))
			return ;
	}
	execute_cmd(data, 0);
}

void	execute_cmd(t_data *data, int flag)
{
	int		i;
	t_pipe	*base;
	t_leaf	*head;

	i = 0;
	base = data->pipe;
	head = data->root;
	while (i < data->info->pipe_num + 1)
	{
		execute_single_cmd(data, base, i, flag);
		i++;
	}
	data->root = head;
	wait_child_processes(data);
}

static void	execute_single_cmd(t_data *data, t_pipe *base, int i, int flag)
{
	if (i < data->info->pipe_num)
		if (pipe(base->com[i].fd) < 0)
			error_code_read("bash", EPIPE, 1);
	base->com[i].pid = fork();
	if (base->com[i].pid == -1)
	{
		if (flag)
			err_msg("bash");
		else
			error_code_read("bash", ENOMEM, 1);
	}
	if (base->com[i].pid == 0)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
		data->info->parent = 1;
		if (data->info->pipe_num != 0)
			if (link_pipe(i, base, data) > 0)
				exit(1);
		do_cmd(data);
	}
	else
		data->root = data->root->right_child;
	if (data->info->pipe_num)
		close_pipe(i, base, data);
}
