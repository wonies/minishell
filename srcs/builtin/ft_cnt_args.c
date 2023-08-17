/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:02:07 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:02:08 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cnt_args(char **args);

int	ft_cnt_args(char **args)
{
	int	count;

	count = 0;
	while (*args != NULL)
	{
		count++;
		args++;
	}
	return (count);
}
