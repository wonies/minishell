/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong <donghong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:41:26 by donghong          #+#    #+#             */
/*   Updated: 2023/08/17 18:38:00 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"
/* init */
void	init(t_data **data, char **env);
void	init_base(int ac);
t_bool	get_input(t_data *data);
void	pipe_init(t_pipe **pipe);
void	info_init(t_info **info);

/* init - ft_base_a.c */
size_t	ft_strlen(const	char *str);
char	*ft_strncat(char *dest, char *src, int n);
char	*ft_strtok(char *str, char *delim);
char	**arr_in_env(t_data *data);
t_list	*env_search(t_data *data, char *key, t_bool flag);
t_bool	check_end(char c);
/* init - ft_base_b.c*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);

/* init - ft_base_token.c */
t_list	*ft_lstnew_token(t_token *token);
t_token	*new_token(void);
t_data	*new_data(void);

/* init - ft_base.c */
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);

/* init - ft_lst.c */
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
/* init - lstclear.c */
void	ft_lstclear(t_list **lst);
void	free_leaf(t_leaf *head);

/* signal*/

void	handle_sigint(int sig);
void	child_handler(int signum);
void	sig(void);

/* lex */
/* lex - lexer.c */
void	free_token(t_token *token);
void	lexer(t_data *data);
void	input_token(t_data *data, t_token **token, int *i);

/* lex - d_sign.c */
void	check_dsign(t_data *data, t_token **token, int *i);

/* lex - d_signcheck.c */
t_bool	check_all(t_data *data, t_token **token, int *i);

/* lex - d_signpre.c */
t_bool	two_space(t_data *data, t_token **token, int *i, int check);
t_bool	pre_check(t_data *data, t_token **token);

/* lex - d_signvar.c */
char	*make_var(t_data *data, int *i, char *var, int *idx);
void	env_exist(t_data *data, t_token **token, int *i, int al_flag);

/* lex - tokenization.c */
void	tokenization(t_data *data, t_token **token, int *i);
void	redirect_check(t_data *data, t_token **token, int *i);
void	token_to_list(t_list **head, t_token **token, int check);

/* lex - possible_env.c */
char	*possible_env_char(t_data *data, char *var);
t_bool	possible_env(t_data *data, t_token **token, char *var);
void	not_env(t_data *data, t_token **token, int *i, char *var);

/* lex - quote_dsign.c */
void	quote_dsign(t_data *data, t_token **token, int *i);

/* lex - quote_evenodd.c */
void	even_quote(t_data *data, t_token **token, int *i, char quote);
void	odd_quote(t_data *data, t_token **token, int *i);

/* lex - quote.c */
void	double_quotes(t_data *data, t_token **token, int *i, int ch);
void	single_quotes(t_data *data, t_token **token, int *i, int ch);
int		find_closing_quote(int i, char *line, char quote);

/* lex - quote_dsign.c */
void	quote_dsign(t_data *data, t_token **token, int *i);
char	*not_space_quo(t_data *data, int *i);
void	space_quo(t_data *data, t_token **token, int *i);
void	signal_quo(t_token **token, int *i);

/* etc - env.c */
t_list	*ft_lstnew(void);
void	env_init(t_data *data, char **env);
char	*find_envp(t_data *data, char *key);
t_bool	env_remove(t_data *data, char *key);
void	env_print(t_data *data);

/* syntax - syntax.c */
t_bool	syn_cmd(t_list *cur);
void	syn_arg(t_list *cur);
t_bool	syn_pipe(t_list *cur);
t_bool	syn_redirect(t_list *cur);
t_bool	syntax(t_data *data);

/* tree - init_leaf.c */
t_leaf	*create_leaf(int leaf_type, t_leaf *parent);
void	init_leaf(t_data *data);
void	create_pipe(t_leaf **cur);

/* tree - add_leaf.c */
void	child_tree(t_leaf *cur_leaf, t_list *cur_token);
t_bool	left_tree(t_leaf *parent, t_token *new_token, int leaf_type);
t_bool	right_tree(t_leaf *parent, t_token *new_token, int leaf_type);

/* err - err_msg */
void	err_msg(char *msg);
void	syntax_err(char *msg);
t_bool	error_code_read(char *str, int code, int flag);
void	print_exit(void);

/* utils - */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putendl_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	ft_lstdel(t_list *lst);

/*free  - */
void	input_free(t_data *data);
void	data_free(t_data *data);

#endif