/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:07 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/16 22:11:00 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		check_redirect(t_leaf *leaf, t_data *data);
static void	do_input_redirect(t_leaf *leaf, t_data *data);
static void	do_output_redirect(t_leaf *leaf, t_data *data);

void	check_redirect(t_leaf *leaf, t_data *data)
{
	t_leaf	*temp;

	temp = leaf->left_child->left_child;
	while (temp)
	{
		if (temp->token->re_type == T_INPUT \
		||temp->token->re_type == T_HEREDOC)
			do_input_redirect(temp, data);
		else if (temp->token->re_type == T_OUTPUT \
		||temp->token->re_type == T_APPEND)
			do_output_redirect(temp, data);
		temp = temp->left_child;
	}
}

static void	do_input_redirect(t_leaf *leaf, t_data *data)
{
	int		fd;
	t_leaf	*temp;

	fd = 0;
	temp = leaf;
	if (temp->token->re_type == T_HEREDOC)
	{
		fd = open (data->info->heredoc_file[data->info->index - 1], \
		O_RDONLY);
		dup2 (fd, STDIN_FILENO);
		return ;
	}
	else if (temp->token->re_type == T_INPUT)
		fd = open (temp->left_child->token->str, O_RDONLY);
	check_file (fd, data);
	dup2 (fd, STDIN_FILENO);
	close (fd);
}

static void	do_output_redirect(t_leaf *leaf, t_data *data)
{
	int		fd;
	t_leaf	*temp;

	fd = 0;
	temp = leaf;
	if (temp->token->re_type == T_APPEND)
	{
		fd = open (temp->left_child->token->str, \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (temp->token->re_type == T_OUTPUT)
	{
		fd = open (temp->left_child->token->str, \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	check_file (fd, data);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
}
