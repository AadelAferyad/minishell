/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:14:38 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/26 11:57:22 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <builtins.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <collector.h>
# include "../parser/parser.h"

typedef struct	environment
{
	char	*key;
	char	*value;
	struct environment	*next;
} t_env;

typedef struct	pipe_line	
{
	int	pipefd[2];
	int	prev_pipe;
} t_pipe;

typedef struct golobal_struct
{
	t_collector	*collector;
	t_env	*env;
	t_cmd	*cmd;
	t_pipe	*_pipe;
	int	exit_status;
}	t_global;

void	create_env(char **env);

extern t_global	g_structs;

void	execution();
void	create_env(char **env);
char	**create_env_arr();

#endif
