/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:24:31 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/07 13:51:44 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <execution.h>
# include <parser.h>
# include <structs.h>

typedef struct golobal_struct
{
	t_collector	*collector;
	t_env		*env;
	t_cmd		*cmd;
	int			exit_status;
}				t_global;

extern t_global	g_structs;

int	execute_redirections(t_reds *redirections, int just_create);
int	n_cmd(t_cmd *cmd);

char	*check_add_path(char *single_cmd);
char	*generate_right_path(char *single_cmd);
#endif
