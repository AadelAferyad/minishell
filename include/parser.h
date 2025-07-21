/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:19:07 by imellali          #+#    #+#             */
/*   Updated: 2025/07/21 21:19:15 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Own Headers */

# include "../libft/libft.h"
# include <minishell.h>
# include <structs.h>

/* Functions's libraries */

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Parser Functions */

t_tokens	*lexer(char *input);
t_cmd		*parse_tokens(t_tokens *tokens);
char		*expand_vars(char *input);
char		**field_splitting(char *value);

/* Lexer/Tokenizer Functions */

int			handle_double_op(char *input, int *i, t_tokens **tokens);
int			handle_single_op(char *input, int *i, t_tokens **tokens);
int			handle_space(char *input, int *i);
int			handle_word(char *input, int *i, t_tokens **tokens,
				int is_heredoc_delim);
int			handle_quoted(char *input, int *i, t_segment **segments,
				int quote_type);
void		handle_unquoted(char *input, int *i, t_segment **segments);
int			handle_assignment(char *input, int *i, t_tokens **tokens);
int			handle_export_and_word(char *input, int *i, t_tokens **tokens,
				int *heredoc);
int			handle_export_quoted(char *input, int *i, int start,
				t_tokens **tokens);
int			handle_export_unquoted(char *input, int *i, int start,
				t_tokens **tokens);
int			lexer_helper_op(char *input, int *i, t_tokens **tokens);
int			update_heredoc_flag(t_tokens *tokens);

/* Memory freeing */

void		free_fields(char **fields);
t_tokens	*cleanup(void);
t_tokens	*lexer_cleanup(void);

/* Expansion Functions */

size_t		handle_env_var(char *input, size_t i, char **output);
char		*get_env_value(char *varname);
void		append_to_output(char **dst, char *src);
size_t		key_end(char *input, size_t i);
char		*join_segs(t_segment *segments);

/* Here-Document Functions */

int			validate_redir_syntax(t_tokens **cur, t_cmd *cmd);
int			process_heredoc_redir(t_tokens *delim_token, t_reds **reds,
				t_cmd *cmd);
int			handle_heredocs(t_reds *reds);
void		append_line(char **buff, const char *line);
void		set_buff(t_reds *redir, char *heredoc_buff);
int			store_line(char **heredoc_buff, char *line, int is_quoted);
int			is_end(char *line, t_reds *redir);

void		append_line(char **buff, const char *line);
t_reds		*get_last_heredoc(t_reds *reds);
void		connect_heredoc(char **heredoc_buff);
void		exit_line(char *flag);
int			heredoc_loop(t_reds *redir, char **heredoc_buff, int is_quoted);

/* Parser Checks */

int			double_pipe(t_tokens *current);
int			pipe_error(t_tokens *current);
void		syntax_error(char *token);
void		redir_error(t_tokens *cur);

/* Char Checks Functions*/

int			ft_isdouble_op(char *input);
int			ft_isop(int c);
int			ft_isspace(int c);
int			is_redir(int type);
int			is_word(int type);
int			is_valid_start(char c);
int			is_valid_char(char c);
int			is_quoted_seg(t_segment *segments);

/* String Manupilation Functions */

int			ft_strcmp(char *s1, char *s2);
char		*extracting_word(char *input, int start, int end);
char		*extract_quoted(char *input, int *i, char quote);
char		*safe_strjoin(char *s1, char *s2);

/* Linked List Functions */

t_tokens	*create_token(t_tokens *tokens, char *value);
int			create_seg(t_tokens **tokens, t_segment *segments);
t_cmd		*add_cmd(t_cmd *head, t_cmd *new_cmd);
t_reds		*add_redir(t_reds *head, t_types type, char *flag, int quoted);
void		add_seg(t_segment **head, t_segment *newseg);
int			add_fields(t_tokens **tokens, char **fields, char *expanded);
int			create_seg_token(t_tokens **tokens, t_segment *segments);

#endif
