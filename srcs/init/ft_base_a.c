/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:43:28 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/08 22:20:39 by wonhshin         ###   ########.fr       */
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

char *ft_find_delim(char *str, char *delim)
{
    char	*deli;
	
	deli = NULL;
	while (*str)
    {
        deli = delim;
        while (*deli)
        {
            if (*str == *deli)
                return (str);
            ++deli;
        }
        ++str;
    }
    return (NULL);
}

char *ft_strtok(char *str, char *delim)
{
    static char *buffer;
	char	*token_start;
	char	*token_end;

    if (str != NULL)
        buffer = str;
    if (buffer == NULL || *buffer == '\0')
        return (NULL);
    token_start = buffer;
    token_end = ft_find_delim(buffer, delim);
    if (token_end != NULL)
    {
        *token_end = '\0';
        buffer = token_end + 1;
    }
    else
        buffer += strlen(buffer);
    return (token_start);
}
