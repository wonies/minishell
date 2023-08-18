/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:08:03 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 21:52:48 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "struct.h"

t_bool	get_input(t_data *data);

void	execute(t_data *data);
void	execute_cmd(t_data *data, int flag);

/*execve utils*/
int		check_builtin(t_data *data);
void	recover_std(t_data *data);
void	heredoc_flag(t_leaf *leaf, t_data *data);
void	error_print(char *cmd, char *option, int flag);

/*child*/
void	do_cmd(t_data *data);
void	exec_fork(t_data *data);
void	check_errortype(char *str, int flag);
t_bool	check_dir(char *command);

/*parent*/
void	wait_child_processes(t_data *data);

int		check_redirect(t_leaf *leaf, t_data *data);

int		fork_heredoc(t_data *data);

/*heredoc_uilts*/
void	write_str(t_data *data, char *content, int fd);

char	*set_path(t_data *data);
void	abs_path(t_data *data);

int		check_file(int fd, t_data *data);
void	close_file(t_data *data);

void	sig(void);
void	handle_sigint(int sig);
void	init_base(int ac);
void	child_handler(int signum);

int		link_pipe(int i, t_pipe *base, t_data *data);
void	close_pipe(int i, t_pipe *base, t_data *data);
void	count_pipe(t_data *data);
void	error_print(char *cmd, char *option, int flag);
int		check_path(char *str);
#endif