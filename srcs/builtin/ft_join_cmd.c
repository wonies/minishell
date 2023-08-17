/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:02:56 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:02:58 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		**ft_join_cmd(t_leaf *leaf);
static int	get_str_cnt(t_leaf *leaf);
static int	get_blank_in_str(char *str);
static char	**input_leaf(t_leaf *leaf, char **input);
static void	devide_str(char **str, char *tmp, int *i);

char	**ft_join_cmd(t_leaf *leaf)
{
	int		cnt_str;
	char	**str;

	cnt_str = get_str_cnt(leaf);
	str = (char **)ft_calloc(cnt_str + 1, sizeof(char *));
	if (!str)
		err_msg("bash");
	str = input_leaf(leaf, str);
	return (str);
}

static int	get_str_cnt(t_leaf *leaf)
{
	int	cnt;

	cnt = 0;
	while (leaf)
	{
		if (!leaf->token->quote)
			cnt += get_blank_in_str(leaf->token->str);
		cnt++;
		leaf = leaf->right_child;
	}
	return (cnt);
}

static int	get_blank_in_str(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			cnt++;
		i++;
	}
	return (cnt);
}

static char	**input_leaf(t_leaf *leaf, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (leaf)
	{
		tmp = ft_strdup(leaf->token->str);
		while (leaf->token->blank == FALSE && leaf->right_child)
		{
			leaf = leaf->right_child;
			tmp = ft_strncat(tmp, leaf->token->str, \
				ft_strlen(leaf->token->str));
		}
		if (!leaf->token->quote)
		{
			devide_str(str, tmp, &i);
			free(tmp);
		}
		else
			str[i++] = tmp;
		leaf = leaf->right_child;
	}
	return (str);
}

static void	devide_str(char **str, char *tmp, int *i)
{
	int	pre_blank;
	int	next_blank;
	int	cnt;

	cnt = get_blank_in_str(tmp) + 1;
	pre_blank = 0;
	next_blank = 0;
	while (cnt--)
	{
		while (check_end(tmp[next_blank]) == FALSE)
			next_blank++;
		str[*i] = ft_substr(tmp, pre_blank, next_blank - pre_blank);
		*i += 1;
		pre_blank = next_blank + 1;
	}
}
