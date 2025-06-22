/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:19:07 by imellali          #+#    #+#             */
/*   Updated: 2025/06/22 14:11:49 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Own Libraries */

# include "../libft/libft.h"

/* Functions's libraries */

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/* Lexer Structures */

typedef enum s_types
{
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
}					t_types;

typedef struct s_tokens
{
	char			*value;
	t_types			type;
	struct s_tokens	*next;
}					t_tokens;

/* Lexer/Tokenizer Functions */

t_tokens			*lexer(char *input);

/* Char Checks Functions*/

int					ft_isdouble_op(char *input);
int					ft_isop(int c);
int					ft_isspace(int c);

/* String Manupilation Functions */

int					ft_strcmp(char *s1, char *s2);

/* Linked List Functions */

t_tokens			*create_token(t_tokens *tokens, char *value);
void				free_list(t_tokens **head);

#endif