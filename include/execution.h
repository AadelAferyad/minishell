/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:14:38 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/20 22:12:23 by aaferyad         ###   ########.fr       */
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
void					setup_types(void);
char					*_strdup(const char *s);
char					*_substr(char const *s, unsigned int start, size_t len);
t_env					**get_env(void);
t_env					*create_node_env(char *key, char *value);
void					free_node(t_env *node, char *buff);
void					create_pwd(char *s, t_env **head, char *buff);
void					export_helper(char **args);
void					add_node_to_env(char *key, char *value);
void					print_export(void);
#endif
