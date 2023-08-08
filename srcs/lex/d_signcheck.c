/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_signcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:18 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/08 22:43:04 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_space(t_data *data, t_token **token, int *i)
{
	int	check;

	check = 0;
	if (data->input[*i] == ' ' || data->input[*i] == '\t')
	{
		if (pre_check(data, token))
			return (1);
		while (data->input[*i] == ' ' || data->input[*i] == '\t')
		{
			++(*i);
			++check;
		}
		if (data->input[*i])
		{
			if (two_space(data, token, i, check))
				return (1);
			--(*i);
		}
		return (1);
	}
	return (0);
}

bool	check_heredoc(t_data *data, t_token **token, int *i)
{
	if (data->tokens && data->tokens->token->re_type == T_HEREDOC)
	{
		(*token)->str = ft_strncat((*token)->str, "$", 1);
		--(*i);
		return (1);
	}
	return (0);
}

bool	check_quote(t_data *data, int *i)
{
	if (data->input[*i] == '\"' || data->input[*i] == '\'')
	{
		--(*i);
		return (1);
	}
	return (0);
}

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
		return ;
	var = make_var(data, i, var, &al_flag);
	if (possible_env(data, token, var))
		not_env(data, token, i, var);
	else
		env_exist(data, token, i, al_flag);
}

bool	check_all(t_data *data, t_token **token, int *i)
{
	if (check_heredoc(data, token, i))
		return (1);
	if (check_quote(data, i))
		return (1);
	if (check_space(data, token, i))
		return (1);
	return (0);
}
