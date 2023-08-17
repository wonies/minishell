/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonhshin <wonhshin@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:08:13 by wonhshin          #+#    #+#             */
/*   Updated: 2023/08/17 13:10:19 by wonhshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# include "struct.h"
/* syntax error msg */
# define E_SYNTAX_PIPE "bash: syntax error near unexpected token `|'"
# define E_SYNTAX_INPUT "bash: syntax error near unexpected token `<'"
# define E_SYNTAX_OUTPUT "bash: syntax error near unexpected token `>'"
# define E_SYNTAX_HEREDOC "bash: syntax error near unexpected token `<<'"
# define E_SYNTAX_APPEND "bash: syntax error near unexpected token `>>'"
# define E_SYNTAX_NEWLINE "bash: syntax error near unexpected token `newline'"

#endif