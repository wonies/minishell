/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:07:41 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 15:08:04 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRUCTURE */

#ifndef STRUCT_H
# define STRUCT_H

# define BUF_SIZE 1024

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

enum	e_type
{
	T_WORD,
	T_PIPE,
	T_CMD,
	T_ARG,
	T_REDIRECT,
	T_INPUT,
	T_OUTPUT,
	T_HEREDOC,
	T_APPEND,
	T_DOUBLE,
	T_SINGLE,
};

typedef struct s_token
{
	int		type;
	int		re_type;
	char	*str;
	t_bool	blank;
	int		quote;
}			t_token;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*pre;
	t_token			*token;
	char			*env;
}				t_list;

typedef struct s_leaf
{
	struct s_leaf	*parent;
	struct s_leaf	*left_child;
	struct s_leaf	*right_child;
	int				leaf_type;
	t_token			*token;
	t_bool			exist;
}				t_leaf;

typedef struct s_pid
{
	pid_t	pid;
	int		fd[2];
}				t_pid;

typedef struct s_pipe
{
	t_pid	*com;
	char	**cmd_path;
	char	*command;
	char	**cmd_abs;
}	t_pipe;

typedef struct s_info
{
	int			index;
	int			heredoc_flag;
	char		**heredoc_file;
	int			oristdin;
	int			oristdout;
	int			pipe_num;
	int			parent;
	int			pipe_index;
}	t_info;

typedef struct s_data
{
	char		*input;
	t_list		*tokens;
	t_list		*envs;
	t_leaf		*root;
	t_pipe		*pipe;
	t_info		*info;
	char		**env_array;
	int			err_code;
}				t_data;

#endif