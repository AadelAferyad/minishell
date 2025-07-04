/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:14:38 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/04 16:10:32 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <builtins.h>
# include <collector.h>

typedef struct	environment
{
	char	*key;
	char	*value;
	struct environment	*next;
} t_env;

typedef struct golobal_struct
{
	t_collector	*collector;
	t_env	*env;
}	t_global;

void	create_env(char **env);

extern t_global	g_structs;

#endif
