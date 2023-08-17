/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:58:10 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 16:58:35 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		link_pipe(int i, t_pipe *base, t_data *data);
void	close_pipe(int i, t_pipe *base, t_data *data);
void	count_pipe(t_data *data);

int	link_pipe(int i, t_pipe *base, t_data *data)
{
	if (i == data->info->pipe_num)
	{
		if (dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 \
		|| close(base->com[i - 1].fd[0]) == -1)
			return (1);
	}
	else if (i == 0)
	{
		if (close(base->com[i].fd[0]) == -1 \
		|| dup2(base->com[i].fd[1], STDOUT_FILENO) == -1 \
		|| close(base->com[i].fd[1]) == -1)
			return (1);
	}
	else
	{
		if (close(base->com[i].fd[0]) == -1 \
		|| dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 \
		|| dup2(base->com[i].fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

void	close_pipe(int i, t_pipe *base, t_data *data)
{
	if (i == data->info->pipe_num)
		close(base->com[i - 1].fd[0]);
	else if (i == 0)
		close(base->com[i].fd[1]);
	else
	{
		close(base->com[i - 1].fd[0]);
		close(base->com[i].fd[1]);
	}
}

void	count_pipe(t_data *data)
{
	t_leaf	*temp;

	temp = data->root;
	while (temp)
	{
		data->info->pipe_num++;
		temp = temp->right_child;
	}
	if (data->info->pipe_num != 0)
		data->info->pipe_num--;
	data->pipe->com = \
		(t_pid *)ft_calloc(data->info->pipe_num + 1, sizeof(t_pid));
	if (!data->pipe->com)
		err_msg("bash");
}
