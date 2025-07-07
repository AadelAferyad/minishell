/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:14:38 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/05 16:28:35 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <builtins.h>
# include <collector.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct environment
{
	char				*key;
	char				*value;
	struct environment	*next;
}						t_env;

void					create_env(char **env);

void					execution(void);
void					create_env(char **env);
char					**create_env_arr(void);
#endif
