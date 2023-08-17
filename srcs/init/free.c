/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:33:57 by donghong          #+#    #+#             */
/*   Updated: 2023/08/16 22:34:25 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input_free(t_data *data)
{
	int	i;

	free(data->input);
	data->input = NULL;
	ft_lstclear(&data->tokens);
	data->tokens = NULL;
	free_leaf(data->root);
	data->root = NULL;
	free(data->pipe->com);
	free(data->pipe);
	i = -1;
	while (++i < data->info->heredoc_flag)
		free(data->info->heredoc_file[i]);
	free(data->info->heredoc_file);
	free(data->info);
}

void	data_free(t_data *data)
{
	free(data->env_array);
	ft_lstclear(&data->envs);
	free(data);
}
