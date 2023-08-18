/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:34:08 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 21:59:49 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	check_blank_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	get_input(t_data *data)
{
	data->input = readline("minishell$ ");
	if (!data->input)
	{
		printf("exit\n");
		g_exit_status = 0;
		exit(0);
	}
	if (check_blank_input(data->input) == TRUE)
	{
		free(data->input);
		return (FALSE);
	}
	add_history(data->input);
	lexer(data);
	if (syntax(data) == FALSE)
	{
		free_leaf(data->root);
		ft_lstclear(&data->tokens);
		free(data->input);
		return (FALSE);
	}
	init_leaf(data);
	pipe_init(&data->pipe);
	info_init(&data->info);
	return (TRUE);
}

void	pipe_init(t_pipe **pipe)
{
	*pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!*pipe)
		err_msg("bash");
}

void	info_init(t_info **info)
{
	*info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!*info)
		err_msg("bash");
	(*info)->oristdin = dup(STDIN_FILENO);
	(*info)->oristdout = dup(STDOUT_FILENO);
}
