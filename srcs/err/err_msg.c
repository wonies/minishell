/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:28:11 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/08 22:28:12 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	err_msg(char *msg)
{
	perror(msg);
	exit(errno);
}

void	syntax_err(char *msg)
{
	printf("%s\n", msg);
	exit(2);
}
