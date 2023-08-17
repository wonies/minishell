/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:03:13 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 15:03:15 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_update_env_export(t_data *data, char *key, char *value);
static char	*get_tmp_key(char *key, t_bool plus);
static void	is_not_plus(t_data *data, \
							char *key, char *value, t_list *search_list);
static void	is_plus(t_data *data, char **tmp, char *value, t_list *search_list);
static void	is_equal(t_data *data, \
							char *key, char *value, t_list *search_list);

void	ft_update_env_export(t_data *data, char *key, char *value)
{
	int		plus;
	char	*tmp;
	t_list	*search_list;

	plus = check_plus(key);
	tmp = get_tmp_key(key, plus);
	search_list = env_search(data, tmp, FALSE);
	if (plus == FALSE)
	{
		is_not_plus(data, key, value, search_list);
		free(tmp);
	}
	else
	{
		is_plus(data, &tmp, value, search_list);
		free(key);
	}
}

static char	*get_tmp_key(char *key, t_bool plus)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup("");
	if (plus == TRUE)
	{
		i = 0;
		while (key[i] != '+')
			i++;
		tmp = ft_strncat(tmp, key, i);
	}
	else if (check_equal(key) == TRUE)
		tmp = ft_strncat(tmp, key, ft_strlen(key) - 1);
	else
		tmp = ft_strncat(tmp, key, ft_strlen(key));
	return (tmp);
}

static void	is_not_plus(t_data *data, \
							char *key, char *value, t_list *search_list)
{
	if (check_equal(key) == FALSE)
	{
		if (search_list)
		{
			free(key);
			free(value);
		}
		else
			ft_add_env_front(data, key, value);
	}
	else
		is_equal(data, key, value, search_list);
}

static void	is_plus(t_data *data, char **tmp, char *value, t_list *search_list)
{
	if (search_list)
	{
		if (check_equal(search_list->env) == TRUE)
			search_list->env = \
				ft_strncat(search_list->env, value, ft_strlen(value));
		else
		{
			search_list->env = ft_strncat(search_list->env, "=", 1);
			search_list->env = \
				ft_strncat(search_list->env, value, ft_strlen(value));
		}
		free(value);
		free(*tmp);
	}
	else
		ft_add_env_front(data, *tmp, value);
}

static void	is_equal(t_data *data, \
							char *key, char *value, t_list *search_list)
{
	if (search_list)
	{
		free(search_list->env);
		if (value)
		{
			search_list->env = ft_strncat(key, value, ft_strlen(value));
			free(value);
		}
		else
			search_list->env = key;
	}
	else
		ft_add_env_front(data, key, value);
}
