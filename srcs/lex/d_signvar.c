/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_signvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:24 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/10 22:10:43 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_var(t_data *data, int *i, char *var, int *idx)
{
	while (data->input[*i] != '\0' && data->input[*i] != ' ' \
	&& data->input[*i] != '\t' && data->input[*i] != '\'' \
	&& data->input[*i] != '\"')
	{
		if (data->input[*i] == '$' || data->input[*i] == '?')
		{
			var = ft_strncat(var, &data->input[(*i)++], 1);
			return (var);
		}
		if (ft_isalnum(data->input[*i]) == 0)
		{
			--(*i);
			*idx = 114;
			break ;
		}
		var = ft_strncat(var, &data->input[(*i)++], 1);
	}
	return (var);
}

void	env_exist(t_data *data, t_token **token, int *i, int al_flag)
{
	if (al_flag == 114)
	{
		while (data->input[*i])
			(*token)->str = ft_strncat((*token)->str, &data->input[++(*i)], 1);
	}
	token_to_list(&data->tokens, token, 1);
}
