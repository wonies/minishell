# ifndef	MINISHELL_H
# define	MINISHELL_H
/* -- include line -- */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
/* syntax error msg */
# define E_SYNTAX_PIPE "bash: syntax error near unexpected token `|'"
# define E_SYNTAX_INPUT "bash: syntax error near unexpected token `<'"
# define E_SYNTAX_OUTPUT "bash: syntax error near unexpected token `>'"
# define E_SYNTAX_HEREDOC "bash: syntax error near unexpected token `<<'"
# define E_SYNTAX_APPEND "bash: syntax error near unexpected token `>>'"
# define E_SYNTAX_NEWLINE "bash: syntax error near unexpected token `newline'"
/* STRUCTURE */
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

enum    e_type
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
};

typedef struct  s_token
{
    int     type;
    int     re_type;
    char    *str;
	bool	space;
}   		t_token; 

typedef struct s_list
{
    struct  s_list *next;
	struct  s_list *pre;
    t_token *token;
    char    *env;
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

typedef struct s_data
{
	char		*input;
	t_list		*tokens;
	t_list		*envs;
    t_leaf      *root;
	int			err_code; // $? 관련해서 작성하기
}				t_data;

/* init */
/* init - ft_base_a.c */
size_t	ft_strlen(const	char *str);
char	*ft_strncat(char *dest, char *src, int n);
char 	*ft_strtok(char *str, char *delim);
/* init - ft_base_b.c*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
/* init - ft_base_token.c */
t_list	*ft_lstnew(t_token *token);
t_token	*new_token();
t_data	*new_data();
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
void    free_leaf(t_leaf *head);
/* lex */
/* lex - lexer.c */
void	free_token(t_token *token);
void	lexer(t_data *data);
void	input_token(t_data *data, t_token **token, int *i);
/* lex - d_sign.c */
void	check_dsign(t_data *data, t_token **token, int *i);
/* lex - d_signcheck.c */
bool	check_all(t_data *data, t_token **token, int *i);
/* lex - d_signpre.c */
bool	two_space(t_data *data, t_token **token, int *i, int check);
bool	pre_check(t_data *data, t_token **token);
/* lex - d_signvar.c */
char	*make_var(t_data *data, int *i, char *var, int *idx);
void	env_exist(t_data *data, t_token **token, int *i, int al_flag);
/* lex - tokenization.c */
void	tokenization(t_data *data, t_token **token, int *i);
void    redirect_check(t_data *data, t_token **token, int *i);
void	token_to_list(t_list **head, t_token **token, int check);
/* lex - possible_env.c */
char	*possible_env_char(t_data *data, char *var);
bool	possible_env(t_data *data, t_token **token, char *var);
void	not_env(t_data *data, t_token **token, int *i, char *var);
/* lex - quote_dsign.c */
void	quote_dsign(t_data *data, t_token **token, int *i);
/* lex - quote_evenodd.c */
void	even_quote(t_data *data, t_token **token, int *i, char quote);
void	odd_quote(t_data *data, t_token **token, int *i);
/* lex - quote.c */
void    double_quotes(t_data *data, t_token **token, int *i, int ch);
void    single_quotes(t_data *data, t_token **token, int *i, int ch);
int		find_closing_quote(int i, char *line, char quote);
/* lex - quote_dsign.c */
void	quote_dsign(t_data *data, t_token **token, int *i);
char	*not_space_quo(t_data *data, t_token **token, int *i);
void	space_quo(t_data *data, t_token **token, int *i);
void	signal_quo(t_data *data, t_token **token, int *i);
/* etc - env.c */
t_list	*ft_lstnews();
void	env_init(t_data *data, char **env);
char    *find_envp(t_data *data, char *key);
void	env_remove(t_data *data, char *key);
/* syntax - syntax.c */
void	syntax(t_data *data);
void	syntax_cmd(t_list	*cur);
void 	syntax_arg(t_list *cur);
void	syntax_redirect(t_list	*cur);
void	syntax_pipe(t_list	*cur);
/* tree - init_leaf.c */
t_leaf	*create_leaf(int leaf_type, t_leaf *parent);
void	init_leaf(t_data *data);
void	create_pipe(t_leaf **cur);
/* tree - add_leaf.c */
void	tree_left_right(t_leaf *cur_leaf, t_list *cur_token);
t_bool	tree_add_left(t_leaf *parent, t_token *new_token, int leaf_type);
t_bool	tree_add_right(t_leaf *parent, t_token *new_token, int leaf_type);
/* err - err_msg */
void	err_msg(char *msg);
void	syntax_err(char *msg);
/* tree_recursive - */
void	print_tree_recursive(t_leaf *node, int level);

#endif
