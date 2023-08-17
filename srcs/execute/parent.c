/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:57:41 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 20:39:39 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_child_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	signal (SIGINT, SIG_IGN);
	while (i < data->info->pipe_num + 1)
	{	
		if (waitpid(data->pipe->com[i].pid, &status, 0) \
			== data->pipe->com[data->info->pipe_num].pid)
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && !data->info->heredoc_flag)
			g_exit_status = 128 + WTERMSIG(status);
		i++;
	}
	if (WTERMSIG (status) == 2)
		ft_putendl_fd("", STDERR_FILENO);
	else if (WTERMSIG (status) == 3)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
	close_file(data);
}
