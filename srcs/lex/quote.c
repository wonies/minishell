/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:39:32 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/15 15:42:01 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	double_quotes(t_data *data, t_token **token, int *i, int ch)
{
	int	end;

	++(*i);
	end = find_closing_quote(*i, data->input, '\"');
	(void)ch;
	(*token)->quote = T_DOUBLE;
	if (end == 0)
	{
		(*token)->str = ft_strncat((*token)->str, &data->input[--(*i)], 1);
		if (data->input[*i + 1] == ' ' || data->input[*i + 1] == '\t')
			(*token)->blank = 1;
		return ;
	}
	else if (end % 2 == 0)
		even_quote(data, token, i, '\"');
	else if (end % 2 != 0)
		odd_quote(data, token, i);
	if (data->input[*i + 1] == ' ' || data->input[*i + 1] == '\t')
		(*token)->blank = 1;
}

void	single_quotes(t_data *data, t_token **token, int *i, int ch)
{
	int	end;

	++(*i);
	end = find_closing_quote(*i, data->input, '\'');
	(void)ch;
	(*token)->quote = T_SINGLE;
	if (end == 0)
	{
		(*token)->str = ft_strncat((*token)->str, &data->input[--(*i)], 1);
		if (data->input[*i + 1] == ' ' || data->input[*i + 1] == '\t')
			(*token)->blank = 1;
		return ;
	}
	else if (end % 2 == 0)
		even_quote(data, token, i, '\'');
	else if (end % 2 != 0)
	{
		while (data->input[*i] != '\'')
			(*token)->str = ft_strncat((*token)->str, &data->input[(*i)++], 1);
	}
	if (data->input[*i + 1] == ' ' || data->input[*i + 1] == '\t')
		(*token)->blank = 1;
}

int	find_closing_quote(int i, char *line, char quote)
{
	int	cnt;

	cnt = 0;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			++cnt;
		++i;
	}
	if (cnt == 0)
		return (0);
	else
		return (cnt + 1);
	return (-1);
}
