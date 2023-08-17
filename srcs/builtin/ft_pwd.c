/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:03:01 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:03:01 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void);

void	ft_pwd(void)
{
	char	*buf;
	size_t	buf_size;

	buf = NULL;
	buf_size = BUF_SIZE;
	while (1)
	{
		buf = (char *)ft_calloc(buf_size, sizeof(char));
		if (!buf)
			err_msg("bash");
		if (getcwd(buf, buf_size) != NULL)
		{
			printf("%s\n", buf);
			free(buf);
			return ;
		}
		free(buf);
		if (buf_size > SIZE_MAX / 2)
			err_msg("bash");
		buf_size *= 2;
	}
}
