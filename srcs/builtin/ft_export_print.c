/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:02:46 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:02:49 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		print_export_order(t_data *data);
void		devide_equal(char *src, char **str1, char **str2, \
							t_bool key_need_equal);
void		free_d_char_ptr(char **str);
static char	**sort_bubble(char **str);
static void	print_export_quote(char **order_set);

void	print_export_order(t_data *data)
{
	int		i;
	char	**order_set;
	char	**order_copy;
	t_list	*cur;

	i = 0;
	cur = data->envs;
	order_copy = (char **)ft_calloc(ft_lstsize(data->envs) + 1, sizeof(char *));
	if (!order_copy)
		err_msg("bash");
	while (cur)
	{
		order_copy[i] = ft_strdup(cur->env);
		cur = cur->next;
		++i;
	}
	order_set = sort_bubble(order_copy);
	print_export_quote(order_set);
	free_d_char_ptr(order_set);
}

void	devide_equal(char *src, char **str1, char **str2, t_bool key_need_equal)
{
	int		equal_len;
	int		value_len;

	equal_len = 0;
	while (src[equal_len] != '=')
		equal_len++;
	equal_len++;
	value_len = ft_strlen(&src[equal_len]);
	if (key_need_equal == TRUE)
		*str1 = ft_substr(src, 0, equal_len);
	else
		*str1 = ft_substr(src, 0, equal_len - 1);
	*str2 = ft_substr(src, equal_len, value_len);
}

void	free_d_char_ptr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

static char	**sort_bubble(char **str)
{
	int		i;
	char	*tmp;
	int		sorted;

	i = 0;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = -1;
		while (str[++i + 1])
		{
			if (ft_strncmp(str[i], str[i + 1], ft_strlen(str[i])) > 0)
			{
				tmp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = tmp;
				sorted = 0;
			}
		}
	}
	return (str);
}

static void	print_export_quote(char **order_set)
{
	int		i;
	char	*str1;
	char	*str2;
	t_bool	flag;

	i = 0;
	while (order_set[i])
	{
		flag = check_equal(order_set[i]);
		devide_equal(order_set[i], &str1, &str2, FALSE);
		printf("declare -x  ");
		if (flag == TRUE)
		{
			if (!str2)
				printf("%s=\"\"\n", str1);
			else
				printf("%s=\"%s\"\n", str1, str2);
		}
		else
			printf("%s\n", str1);
		free(str1);
		free(str2);
		++i;
	}
}
