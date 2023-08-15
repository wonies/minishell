/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dsign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:13:12 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 15:42:43 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_quo(t_data *data, t_token **token, int *i)
{
	char	*tmp_var;

	tmp_var = ft_itoa(data->err_code);
	(*token)->str = ft_strncat((*token)->str, tmp_var, ft_strlen(tmp_var));
	++(*i);
	free(tmp_var);
}

void	space_quo(t_data *data, t_token **token, int *i)
{
	(*token)->str = ft_strncat((*token)->str, "$", 1);
	while (data->input[*i] != '"')
		(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
	(*i)++;
}

char	*not_space_quo(t_data *data, t_token **token, int *i)
{
	char	*tmp;

	while (data->input[*i] != ' ' && data->input[*i] != '\t' \
	&& data->input[*i] != '\"')
	{
		if (ft_isalnum(data->input[*i]) == 0)
			break ;
		tmp = ft_strncat(tmp, &data->input[(*i)++], 1);
	}
	return (tmp);
}

void	quote_dsign(t_data *data, t_token **token, int *i)
{
	char	*temp;
	char	*envs;

	++(*i);
	envs = NULL;
	if (data->input[*i] == '?')
		signal_quo(data, token, i);
	temp = ft_strdup("");
	if (data->input[*i] == ' ')
		space_quo(data, token, i);
	temp = not_space_quo(data, token, i);
	envs = possible_env_char(data, temp);
	if (envs)
		(*token)->str = ft_strncat((*token)->str, envs, ft_strlen(envs));
	else
		(*i) -= ft_strlen(temp) + 1;
	free(temp);
	free(envs);
}
