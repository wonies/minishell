/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:43:40 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 12:35:31 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	char	*str;
	int		len;

	len = ft_strlen(s1);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		err_msg("bash");
	temp = str;
	if (!temp)
		return (NULL);
	while (*s1)
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	*temp = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;

	s1_cpy = (unsigned char *)s1;
	s2_cpy = (unsigned char *)s2;
	while ((*s1_cpy || *s2_cpy) && n > 0)
	{
		if (*s1_cpy != *s2_cpy || n == 0)
			return (*s1_cpy - *s2_cpy);
		s1_cpy++;
		s2_cpy++;
		n--;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*string;
	size_t	size;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
		size = 0;
	else if (len > ft_strlen(s + start))
		size = ft_strlen(s + start);
	else
		size = len;
	string = (char *)malloc(sizeof(char) * (size + 1));
	if (!string || !s)
		err_msg("bash");
	if (size)
		while (i < len && s[start])
			string[i++] = s[start++];
	string[i] = '\0';
	return (string);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	temp = malloc(count * size);
	if (!temp)
		err_msg("bash");
	ft_memset(temp, 0, count * size);
	return (temp);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)b;
	while (len-- > 0)
		*temp++ = (unsigned char)c;
	return (b);
}
