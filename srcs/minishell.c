/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:06:43 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 17:56:26 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = new_data();
	env_init(data, env);
	init_base(ac);
	data->env_array = arr_in_env(data);
	if (!data->env_array)
		err_msg("bash");
	while (TRUE)
	{
		sig();
		if (get_input(data) == FALSE)
			continue ;
		execute(data);
		input_free(data);
	}
	data_free(data);
	return (0);
}
