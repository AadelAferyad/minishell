/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:19:07 by imellali          #+#    #+#             */
/*   Updated: 2025/07/05 02:17:11 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Own Headers */

# include "../libft/libft.h"
# include <execution.h>

/* Functions's libraries */

# include <readline/history.h>
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
}						t_types;

typedef enum e_qtypes
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
}						t_qtypes;

typedef struct s_segment
{
	char				*value;
	t_qtypes			q_type;
	struct s_segment	*next;
}						t_segment;

typedef struct s_tokens
{
	char				*value;
	t_types				type;
	t_segment			*segments;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_reds
{
	t_types				type;
	char				*flag;
	struct s_reds		*next;
}						t_reds;

typedef struct s_cmd
{
	char				**args;
	t_reds				*reds;
	struct s_cmd		*next;
}						t_cmd;

/* Parser Functions */

t_tokens				*lexer(char *input);
t_cmd					*parse_tokens(t_tokens *tokens);
char					*expand_vars(char *input);

/* Lexer/Tokenizer Functions */

int						handle_double_op(char *input, int *i,
							t_tokens **tokens);
int						handle_single_op(char *input, int *i,
							t_tokens **tokens);
int						handle_space(char *input, int *i);
int						handle_word(char *input, int *i, t_tokens **tokens);
int						handle_quoted(char *input, int *i, t_segment **segments,
							int quote_type);
void					handle_unquoted(char *input, int *i,
							t_segment **segments);

/* Expansion Functions */

size_t					handle_env_var(char *input, size_t i, char **output);
char					*get_env_value(char *varname);
void					append_to_output(char **dst, char *src);
size_t					key_end(char *input, size_t i);

/* Parser Checks */

int						double_pipe(t_tokens *current);
int						pipe_error(t_tokens *current);
void					syntax_error(char *token);
void					redir_error(t_tokens *cur);

/* Char Checks Functions*/

int						ft_isdouble_op(char *input);
int						ft_isop(int c);
int						ft_isspace(int c);
int						is_redir(int type);
int						is_word(int type);

/* String Manupilation Functions */

int						ft_strcmp(char *s1, char *s2);
char					*extracting_word(char *input, int start, int end);
char					*extract_quoted(char *input, int *i, char quote);
char					*safe_strjoin(char *s1, char *s2);

/* Linked List Functions */

t_tokens				*create_token(t_tokens *tokens, char *value);
int						create_seg(t_tokens **tokens, t_segment *segments);
t_cmd					*add_cmd(t_cmd *head, t_cmd *new_cmd);
t_reds					*add_redir(t_reds *head, t_types type, char *flag);
void					add_seg(t_segment **head, t_segment *newseg);

#endif