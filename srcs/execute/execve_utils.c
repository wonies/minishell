/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:57:04 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 21:56:23 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_builtin(t_data *data);
void	recover_std(t_data *data);
void	heredoc_flag(t_leaf *leaf, t_data *data);

int	check_builtin(t_data *data)
{
	int		built;
	t_leaf	*temp;

	temp = data->root->left_child->right_child;
	if (temp != NULL)
		built = check_builtin_func(temp->token->str);
	if (temp == NULL)
	{
		check_redirect(data->root, data);
		recover_std(data);
		return (TRUE);
	}
	if (built != 0)
	{
		if (!check_redirect(data->root, data))
			return (1);
		g_exit_status = exec_builtin(built, data);
		recover_std(data);
		return (TRUE);
	}
	return (FALSE);
}

void	recover_std(t_data *data)
{
	if (dup2(data->info->oristdin, STDIN_FILENO) == -1)
		error_code_read("Bad file descriptor", EBADF, 1);
	close(data->info->oristdin);
	if (dup2(data->info->oristdout, STDOUT_FILENO) == -1)
		error_code_read("Bad file descriptor", EBADF, 1);
	close(data->info->oristdin);
}

void	heredoc_flag(t_leaf *leaf, t_data *data)
{
	if (!leaf)
		return ;
	if (leaf->token)
	{
		if (leaf->token->type == T_REDIRECT)
		{
			if (leaf->token->re_type == T_HEREDOC)
			{
				if (leaf->left_child == NULL)
					return ;
				data->info->heredoc_flag++;
			}
		}
	}
	heredoc_flag(leaf->left_child, data);
	heredoc_flag(leaf->right_child, data);
}
