/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:58:03 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 16:58:03 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*set_path(t_data *data);
void		abs_path(t_data *data);
int			check_path(char *str);
char		*search_path(t_pipe *base);
static char	**get_path_envp(char **env);

char	*set_path(t_data *data)
{
	char	*tmp;
	t_pipe	*base;

	base = data->pipe;
	if (!base->cmd_path)
		exit(1);
	if (check_path(base->cmd_path[0]) == TRUE)
	{
		tmp = ft_strdup(base->cmd_path[0]);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		return (NULL);
	}
	return (search_path(base));
}

void	abs_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	data->pipe->cmd_abs = get_path_envp(data->env_array);
	if (!data->pipe->cmd_abs || !data->pipe->cmd_abs[1])
		return ;
	while (data->pipe->cmd_abs[i])
	{
		temp = data->pipe->cmd_abs[i];
		data->pipe->cmd_abs[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}

int	check_path(char *str)
{
	if (!ft_strncmp("./", str, 2) || \
		!ft_strncmp("../", str, 3) || \
		!ft_strncmp("/", str, 1))
		return (1);
	return (0);
}

char	*search_path(t_pipe *base)
{
	char	*tmp;
	int		k;

	k = 0;
	if (!base->cmd_abs)
	{
		error_print(base->cmd_path[0], 0, 1);
		exit (127);
	}
	while (base->cmd_abs[k])
	{
		tmp = ft_strjoin(base->cmd_abs[k], base->cmd_path[0]);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		k++;
	}
	return (NULL);
}

static char	**get_path_envp(char **env)
{
	char	*path;
	int		i;

	i = 0;
	if (*env == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = env[i];
			return (ft_split(path, ':'));
		}
		i++;
	}
	return (NULL);
}
