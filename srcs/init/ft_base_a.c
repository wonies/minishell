/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:43:28 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/07 23:46:12 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const	char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strncat(char *dest, char *src, int n)
{
	int		size;
	char	*res;
	int		i;

	size = ft_strlen(dest) + n;
	res = (char *)ft_calloc(size + 1, sizeof(char));
	i = 0;
	if (dest)
		while (*dest)
			res[i++] = *dest++;
	if (src)
		while (n--)
			res[i++] = *src++;
	return (res);
}

char	*ft_strtok(char *str, char *delim)
{
	char	*buffer;
	char	*deli;

	if (!str)
		return (NULL);
	else
		buffer = str;
	while (*buffer)
	{
		deli = delim;
		while (*deli)
		{
			if (*buffer == *deli)
			{
				// *buffer = NULL;
				++deli;
				return (str);
			}
			++deli;
		}
		++buffer;
	}
	return (str);
}
