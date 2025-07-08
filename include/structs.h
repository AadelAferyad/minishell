/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:34:11 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/08 16:34:29 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef enum e_cmd_type
{
	BUILTINS,
	OUTSIDER,
}						t_cmd_type;

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
	int					quoted;
	char				*heredoc_buff;
	struct s_reds		*next;
}						t_reds;

typedef struct s_cmd
{
	char				**args;
	t_cmd_type			type;
	t_reds				*reds;
	struct s_cmd		*next;
}						t_cmd;

#endif
