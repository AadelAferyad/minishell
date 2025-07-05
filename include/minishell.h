/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:24:31 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/05 16:36:58 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <execution.h>
# include "../parser/structs.h"
# include "../parser/parser.h"

typedef struct golobal_struct
{
	t_collector	*collector;
	t_env	*env;
	t_cmd	*cmd;
	int	exit_status;
}	t_global;

extern t_global	g_structs;
#endif
