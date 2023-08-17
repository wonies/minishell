/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:51:05 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 16:51:06 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		error_print(char *cmd, char *option, int flag);
void		check_errortype(char *str, int flag);
static char	*ft_strjoinstr(char *s1, char *s2);

void	error_print(char *cmd, char *option, int flag)
{
	char	*tmp;
	char	*str;

	str = ft_strdup(cmd);
	tmp = str;
	str = ft_strjoinstr("bash: ", str);
	free(tmp);
	if (option)
	{
		tmp = str;
		str = ft_strjoin(str, ": ");
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, option);
		free(tmp);
	}
	check_errortype(str, flag);
}

void	check_errortype(char *str, int flag)
{
	char	*tmp;

	tmp = str;
	if (flag == 0)
		str = ft_strjoinstr(str, ": command not found\n");
	else if (flag == 1)
		str = ft_strjoinstr(str, ": No such file or directory\n");
	else if (flag == 2)
	{
		str = ft_strjoinstr(str, ": is a directory\n");
	}
	else if (flag == 3)
	{
		str = "bash: exit: too many arguments\n";
		write(2, str, ft_strlen (str));
		return ;
	}
	else if (flag == 4)
	{
		write(2, "bash: exit: ", 12);
		str = ft_strjoinstr(str, " numeric argument required\n");
	}
	free(tmp);
	write(2, str, ft_strlen (str));
	free(str);
}

static char	*ft_strjoinstr(char *s1, char *s2)
{
	char	*tmp;
	size_t	lena;
	size_t	lenb;

	if (s1 == 0 || s2 == 0)
		return (0);
	lena = ft_strlen(s1);
	lenb = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (lena + lenb + 1));
	if (!tmp)
		return (0);
	tmp[0] = '\0';
	ft_strlcat(tmp, s1, lena + 1);
	ft_strlcat(tmp, s2, lena + lenb + 1);
	tmp[lena + lenb] = '\0';
	return (tmp);
}
