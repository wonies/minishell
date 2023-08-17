/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dsign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:13:12 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 18:33:52 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_quo(t_token **token, int *i)
{
	char	*tmp_var;

	tmp_var = ft_itoa(g_exit_status);
	(*token)->str = ft_strncat((*token)->str, tmp_var, ft_strlen(tmp_var));
	++(*i);
	free(tmp_var);
}

void	space_quo(t_data *data, t_token **token, int *i)
{
	if (g_exit_status != 0)
		return ;
	(*token)->str = ft_strncat((*token)->str, "$", 1);
	while (data->input[*i] != '"')
		(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
	(*i)++;
}

char	*not_space_quo(t_data *data, int *i)
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
	int		ques;

	++(*i);
	envs = NULL;
	ques = 0;
	if (data->input[*i] == '?')
	{
		signal_quo(token, i);
		return ;
	}
	temp = ft_strdup("");
	if (data->input[*i] == ' ')
		space_quo(data, token, i);
	temp = not_space_quo(data, i);
	envs = possible_env_char(data, temp);
	if (envs)
		(*token)->str = ft_strncat((*token)->str, envs, ft_strlen(envs));
	else
		(*i) -= ft_strlen(temp) + 1;
	free(temp);
	free(envs);
}
