/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:24:31 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/21 21:22:55 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <execution.h>

# include <signal.h>
# include <structs.h>
# include <parser.h>
# include <limits.h>

# define MAX 9223372036854775807

typedef struct golobal_struct
{
	t_collector	*collector;
	t_cmd		*cmd;
	int			exit_status;
}				t_global;

extern t_global	g_structs;

int				execute_redirections(t_reds *redirections, int just_create);
int				n_cmd(t_cmd *cmd);
char			*check_add_path(char *single_cmd);
char			*generate_right_path(char *single_cmd);
void			signal_handler(int sig);
void			execute_pipes(int n_cmd, int **pipefd, int i_cmd);
void			execute_outsider_cmd(t_cmd *cmd);
void			execute_builtins_cmd(t_cmd *cmd);
void			execute_multiple_command(int num_cmd);
void			builting_exit(void);
pid_t			execute_one_command(t_cmd *cmd, int n_cmd,
					int **pipefd, int i_cmd);
#endif
