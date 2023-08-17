/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:02:21 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 18:41:04 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_exit(t_data *data);
static void	arg_over_one(int count, char **cmd, int flag);
static void	arg_over_two(int count, char **cmd, int flag);
static void	exit_not_num(char *str);
static int	is_num_str(char *str);

void	ft_exit(t_data *data)
{
	long long	status;
	char		**cmd;
	int			count;
	int			flag;

	cmd = ft_join_cmd(data->root->left_child->right_child);
	count = ft_cnt_args(cmd);
	flag = 1;
	status = 0;
	if (count == 1)
	{
		printf("exit\n");
		exit(status);
	}
	else
		arg_over_one(count, cmd, flag);
	free_d_char_ptr(cmd);
}

static void	arg_over_one(int count, char **cmd, int flag)
{
	int	status;

	if (count == 2)
	{
		if (!ft_strncmp("-9223372036854775808", cmd[1], 20))
		{
			printf("exit\n");
			g_exit_status = 0;
			exit(0);
		}
		status = ft_atolong(cmd[1], &flag);
		if (flag && is_num_str(cmd[1]) && ft_strlen(cmd[1]) <= 20)
		{
			printf("exit\n");
			g_exit_status = status % 256;
			exit(status % 256);
		}
		exit_not_num(cmd[1]);
	}
	else
		arg_over_two(count, cmd, flag);
}

static void	arg_over_two(int count, char **cmd, int flag)
{
	int			i;

	i = 1;
	ft_atolong(cmd[1], &flag);
	while (i < count)
	{
		if (flag && is_num_str(cmd[i]) && ft_strlen(cmd[i]) <= 20)
		{
			check_errortype("error", 3);
			g_exit_status = 1;
			break ;
		}
		else
			exit_not_num(cmd[i]);
		++i;
	}
}

static void	exit_not_num(char *str)
{
	check_errortype(str, 4);
	g_exit_status = 255;
	exit(255);
}

static int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
