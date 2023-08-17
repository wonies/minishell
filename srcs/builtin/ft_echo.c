/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:02:11 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:02:13 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_echo(t_leaf *arg);
static void	check_flag(t_leaf *arg, int *cnt, int *flag);
static void	print_line(t_leaf *arg);

void	ft_echo(t_leaf *arg)
{
	int	cnt;
	int	flag;

	cnt = 0;
	flag = FALSE;
	check_flag(arg, &cnt, &flag);
	while (cnt--)
		arg = arg->right_child;
	while (arg)
	{
		print_line(arg);
		if (arg->token->blank == TRUE && arg->right_child)
			printf(" ");
		arg = arg->right_child;
	}
	if (flag == FALSE)
		printf("\n");
}

static void	check_flag(t_leaf *arg, int *cnt, int *flag)
{
	int	i;

	while (arg && arg->token->str[0] == '-' && arg->token->str[1] == 'n')
	{
		i = 1;
		while (arg->token->str[i] != '\0')
		{
			if (arg->token->str[i] != 'n')
				return ;
			i++;
		}
		arg = arg->right_child;
		*cnt += 1;
		*flag = TRUE;
	}
}

static void	print_line(t_leaf *arg)
{
	int	i;

	i = 0;
	while (arg->token->str[i])
	{
		printf("%c", arg->token->str[i]);
		i++;
	}
}
