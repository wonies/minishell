NAME = minishell

INCS_DIR    = includes
SRCS_DIR    = srcs
OBJS_DIR    = objs
READ_DIR = ~/.brew/opt/readline

CC = cc
CFLAGS = -Wall -Wextra -Werror  -I $(READ_DIR)/include 
RLFLAGS = -lreadline -ltermcap
RM = rm -rf

HEADER	=	includes/minishell.h
MAKE = make

SRCS =	minishell.c \
	init/init.c \
	init/free.c \
	init/split.c \
	init/utils.c \
	initialize/base_a.c \
	initialize/base_b.c \
	initialize/base_token.c \
	initialize/base.c \
	initialize/lst.c \
	initialize/lstclear.c \
	lex/d_signpre.c \
	lex/quote_dsign.c \
	lex/d_signcheck.c \
	lex/d_signvar.c \
	lex/d_sign.c \
	lex/possible_env.c \
	lex/lexer.c \
	lex/quote_evenodd.c \
	lex/quote.c \
	lex/tokenize.c \
	tree/add_leaf.c \
	tree/init_leaf.c  \
	err/err_msg.c \
	err/error.c \
	etc/env.c \
	etc/envutils.c \
	syntax/syntax.c \
	builtin/builtin.c \
	builtin/ft_join_cmd.c \
	builtin/ft_cnt_args.c \
	builtin/ft_update_env_cd.c \
	builtin/ft_update_env_export.c \
	builtin/ft_add_env_front.c \
	builtin/ft_cd.c \
	builtin/ft_echo.c \
	builtin/ft_exit.c \
	builtin/ft_pwd.c \
	builtin/ft_unset.c \
	builtin/ft_export.c \
	builtin/ft_export_print.c \
	builtin/ft_export_check.c \
	builtin/ft_env.c \
	builtin/ft_atolong.c \
	execute/execve.c \
	execute/execve_utils.c \
	execute/child.c \
	execute/parent.c \
	execute/pipe.c \
	execute/path.c \
	execute/file.c \
	redirect/heredoc_parser.c \
	redirect/heredoc.c \
	redirect/redirect.c \
	signal/signal.c 
	
SRCS_WITH_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_WITH_PATH:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all : $(NAME)

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	@$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCS_DIR)

${OBJS_DIR}:
	@mkdir ${OBJS_DIR}
	@mkdir ${OBJS_DIR}/init
	@mkdir ${OBJS_DIR}/initialize
	@mkdir ${OBJS_DIR}/err
	@mkdir ${OBJS_DIR}/etc
	@mkdir ${OBJS_DIR}/lex
	@mkdir ${OBJS_DIR}/tree
	@mkdir ${OBJS_DIR}/redirect
	@mkdir ${OBJS_DIR}/syntax
	@mkdir ${OBJS_DIR}/builtin
	@mkdir ${OBJS_DIR}/execute
	@mkdir ${OBJS_DIR}/signal

${NAME}: ${OBJS}
	@echo "---------------------------"
	@echo "|                         |"
	@echo "|        MINISHELL        |"
	@echo "|                         |"
	@echo "---------------------------"
	@$(CC) $(RLFLAGS) $^ -o $@ -I $(INCS_DIR) -L $(READ_DIR)/lib

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_DIR)

fclean:
	@$(MAKE) clean
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
