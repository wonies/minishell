/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_sign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:43:46 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 15:43:47 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_dsign(t_data *data, t_token **token, int *i)
{
	char	*var;
	int		al_flag;

	++(*i);
	var = ft_strdup("");
	al_flag = 0;
	if (!var)
		return ;
	if (check_all(data, token, i))
	{
		free(var);
		return ;
	}
	var = make_var(data, i, var, &al_flag);
	if (data->input[*i] == '\"' || data->input[*i] == '\'' || \
	data->input[*i] == ' ' || data->input[*i] == '\t')
			(*i)--;
	if (possible_env(data, token, var))
		not_env(data, token, i, var);
	else
		env_exist(data, token, i, al_flag);
	free(var);
}
