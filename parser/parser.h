/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:19:07 by imellali          #+#    #+#             */
/*   Updated: 2025/06/29 05:44:39 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Own Headers */

# include "../libft/libft.h"
# include <execution.h>

/* Functions's libraries */

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Parser Structures */

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

typedef struct s_reds
{
	t_types			type;
	char			*flag;
	struct s_reds	*next;
}					t_reds;

typedef struct s_cmd
{
	char			**args;
	t_reds			*reds;
	struct s_cmd	*next;
}					t_cmd;

/* Lexer/Tokenizer Functions */

t_tokens			*lexer(char *input);
int					handle_double_op(char *input, int *i, t_tokens **tokens);
int					handle_single_op(char *input, int *i, t_tokens **tokens);
int					handle_single_qt(char *input, int *i, t_tokens **tokens);
int					handle_double_qt(char *input, int *i, t_tokens **tokens);
int					handle_word(char *input, int *i, t_tokens **tokens);
int					handle_space(char *input, int *i);

/* Parser Functions */

t_cmd				*parse_tokens(t_tokens *tokens);

/* Parser Checks */

int					is_pipe(char *token);
int					double_pipe(t_tokens *current);
int					pipe_error(t_tokens *current);
int					get_redir_type(char *token);
void				syntax_error(char *token);

/* Char Checks Functions*/

int					ft_isdouble_op(char *input);
int					ft_isop(int c);
int					ft_isspace(int c);

/* String Manupilation Functions */

int					ft_strcmp(char *s1, char *s2);
char				*extracting_word(char *input, int start, int end);

/* Linked List Functions */

t_tokens			*create_token(t_tokens *tokens, char *value,
						t_qtypes qtype);
void				free_list(t_tokens **head);
t_cmd				*add_cmd(t_cmd *head, t_cmd *new_cmd);
t_reds				*add_redir(t_reds *head, t_types type, char *flag);

#endif