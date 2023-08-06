#include "../../includes/minishell.h"

void	err_msg(char *msg)
{
	perror(msg);
	exit(errno);
}

void	syntax_err(char *msg)
{
	printf("%s\n", msg);
	exit(2);
}
