/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:02:52 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 21:27:43 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool			ft_export(t_data *data, t_leaf *arg);
static int		cnt_args(t_leaf *tmp);
static void		join_str(t_leaf **cur, char **tmp);
static t_bool	start_export(t_data *data, char *tmp);

t_bool	ft_export(t_data *data, t_leaf *cmd)
{
	int		args_cnt;
	char	*tmp;

	args_cnt = cnt_args(cmd->right_child);
	if (!cmd || args_cnt == 0)
	{
		print_export_order(data);
		return (TRUE);
	}
	cmd = cmd->right_child;
	while (args_cnt--)
	{
		join_str(&cmd, &tmp);
		if (start_export(data, tmp) == FALSE)
			return (FALSE);
	}
	update_env_double_char(data);
	return (TRUE);
}

static void	join_str(t_leaf **cur, char **tmp)
{
	*tmp = ft_strdup((*cur)->token->str);
	while (!(*cur)->token->blank && (*cur)->right_child)
	{
		*cur = (*cur)->right_child;
		*tmp = ft_strncat(*tmp, (*cur)->token->str, \
			ft_strlen((*cur)->token->str));
	}
	*cur = (*cur)->right_child;
}

static int	cnt_args(t_leaf *tmp)
{
	int	args;

	args = 0;
	while (tmp)
	{
		if (tmp->token && tmp->token->type == T_ARG && tmp->token->blank == 1)
			++args;
		if (!tmp->right_child && tmp->token->blank == 0)
			++args;
		tmp = tmp->right_child;
	}
	return (args);
}

static t_bool	start_export(t_data *data, char *tmp)
{
	char	*str1;
	char	*str2;

	if (check_equal(tmp) == TRUE)
	{
		devide_equal(tmp, &str1, &str2, TRUE);
		free(tmp);
		if (check_env(data, str1, str2) == FALSE)
			return (FALSE);
	}
	else
		if (check_env(data, tmp, NULL) == FALSE)
			return (FALSE);
	return (TRUE);
}
