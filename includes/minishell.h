# ifndef	MINISEHLL_H
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
}				t_data;

/* init - ft_base_a.c */
size_t	ft_strlen(const	char *str);
char	*ft_strncat(char *dest, char *src, int n);
char 	*ft_strtok(char *str, const char *delim);
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
/* init - ft_base_b.c*/
int	ft_isalnum(int c);

/* lex - lexer.c */
void	lexer(t_data *data);
void	input_token(t_data *data, t_token **token, int *i);
/* lex - prepare_lex.c */
t_list	*ft_lstnew(t_token *token);
t_token	*new_token();
t_data	*new_data();
void	token_to_list(t_list **head, t_token **token, int check);
/* lex - tokenization.c */
void	tokenization(t_data *data, t_token **token, int *i);
void    redirect_check(t_data *data, t_token **token, int *i);
/* lex - quote.c */
void    double_quotes(t_data *data, t_token **token, int *i, int ch);
void    single_quotes(t_data *data, t_token **token, int *i, int ch);
void	quote_dsign(t_data *data, t_token **token, int *i);
int		find_closing_quote(int i, char *line, char quote);
/* lex - quote_evenodd.c */
void	even_quote(t_data *data, t_token **token, int *i, char quote);
void	odd_quote(t_data *data, t_token **token, int *i);
/* lex - d_signcheck.c */
bool	check_space(t_data *data, t_token **token, int *i);
bool	two_space(t_data *data, t_token **token, int *i, int check);
bool	check_quote(t_data *data, int *i);
void	check_dsign(t_data *data, t_token **token, int *i);
bool	check_all(t_data *data, t_token **token, int *i);
/* lex- - d_sign.c */
bool	pre_check(t_data *data, t_token **token);
void	not_env(t_data *data, t_token **token, int *i, char *var);
bool    possible_env(t_data *data, t_token **token, int *i, char *var);
char    *possible_env_char(t_data *data, t_token **token, int *i, char *var);
/* etc - env.c */
t_list	*ft_lstnews();
void	env_init(t_data *data, char **env);
void    get_envp(t_data *data);
char    *find_envp(t_data *data, char *key);





#endif
