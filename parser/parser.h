/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:19:07 by imellali          #+#    #+#             */
/*   Updated: 2025/06/23 16:00:00 by imellali         ###   ########.fr       */
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

typedef enum e_types
{
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
}					t_types;

typedef enum e_qtypes
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
}					t_qtypes;

typedef struct s_tokens
{
	char			*value;
	t_types			type;
	t_qtypes		quote_type;
	struct s_tokens	*next;
}					t_tokens;

/* Lexer/Tokenizer Functions */

t_tokens			*lexer(char *input);
int					handle_double_op(char *input, int *i, t_tokens **tokens);
int					handle_single_op(char *input, int *i, t_tokens **tokens);
int					handle_single_qt(char *input, int *i, t_tokens **tokens);
int					handle_double_qt(char *input, int *i, t_tokens **tokens);
int					handle_word(char *input, int *i, t_tokens **tokens);
int					handle_space(char *input, int *i);
char				*extract_word(char *input, int start, int end,
						t_tokens **tokens);

/* Char Checks Functions*/

int					ft_isdouble_op(char *input);
int					ft_isop(int c);
int					ft_isspace(int c);

/* String Manupilation Functions */

int					ft_strcmp(char *s1, char *s2);

/* Linked List Functions */

t_tokens			*create_token(t_tokens *tokens, char *value,
						t_qtypes qtype);
void				free_list(t_tokens **head);

#endif