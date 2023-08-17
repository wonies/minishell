/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:40 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 14:32:41 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	not_env(t_data *data, t_token **token, int *i, char *var)
{
	int	var_len;

	var_len = ft_strlen(var);
	if (!(*(*token)->str))
	{
		free((*token)->str);
		free (*token);
		(*token) = new_token();
	}
	if (data->input[*i] != ' ' || data->input[*i] != '\t')
	{
		if (var_len == 0)
		{
			(*token)->str = ft_strncat((*token)->str, "$", 1);
			return ;
		}
		++(*i);
		if (!ft_isalnum(data->input[*i]))
			--(*i);
		return ;
	}
}

t_bool	possible_env(t_data *data, t_token **token, char *var)
{
	char	*temp;
	char	*value;
	char	*var_tmp;

	var_tmp = ft_strdup(var);
	if (find_envp(data, var_tmp) == NULL)
	{
		free(var_tmp);
		return (1);
	}
	temp = ft_strdup(find_envp(data, var_tmp));
	if (temp != NULL)
	{
		value = ft_strtok(temp, "=");
		value = ft_strtok(NULL, "=");
		(*token)->str = ft_strncat((*token)->str, value, ft_strlen(value));
		free(var_tmp);
		free (temp);
		return (0);
	}
	free (var_tmp);
	free(temp);
	return (1);
}

char	*possible_env_char(t_data *data, char *var)
{
	char	*temp;
	char	*value;
	char	*var_temp;
	char	*copy_value;

	var_temp = ft_strdup(var);
	if (find_envp(data, var_temp) == NULL)
	{
		free(var_temp);
		return (NULL);
	}
	temp = ft_strdup(find_envp(data, var_temp));
	if (temp != NULL)
	{
		value = ft_strtok(temp, "=");
		value = ft_strtok(NULL, "=");
		copy_value = ft_strdup(value);
		free(temp);
		free(var_temp);
		return (copy_value);
	}
	return (NULL);
}
