NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ~/.brew/opt/readline/include
LDFLAGS = -L ~/.brew/opt/readline/lib -lreadline -ltermcap
RM = rm -f

HEADER	=	includes/minishell.h

SRCS =	srcs/minishell.c \
	srcs/print_recursive.c \
	srcs/init/ft_base_a.c \
	srcs/init/ft_base_b.c \
	srcs/init/ft_base_token.c \
	srcs/init/ft_base.c \
	srcs/init/ft_lst.c \
	srcs/lex/d_sign.c \
	srcs/lex/d_signcheck.c \
	srcs/lex/d_signvar.c \
	srcs/lex/lexer.c \
	srcs/lex/quote_evenodd.c \
	srcs/lex/quote.c \
	srcs/lex/tokenize.c \
	srcs/tree/add_leaf.c \
	srcs/tree/init_leaf.c  \
	srcs/err/err_msg.c \
	srcs/etc/env.c \
	srcs/syntax/syntax.c \

M_OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(M_OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(M_OBJS) $(LDFLAGS)

clean:
	$(RM) $(M_OBJS)

fclean: 
	make clean
	$(RM) $(NAME)

re: 
	make fclean 
	make all
	
.PHONY: all clean fclean re
