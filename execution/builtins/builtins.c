/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:46:07 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/21 20:06:06 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env(void)
{
	t_env	*tmp;

	tmp = *get_env();
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_structs.exit_status = 0;
}

t_env	*create_node_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->key = _strdup(key);
	node->value = _strdup(value);
	node->next = NULL;
	if (!node || !node->key || !node->value)
	{
		free_collector_all(0);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	return (node);
}

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	g_structs.exit_status = 0;
	return (0);
}

void	builtin_export(char **args)
{
	if (!args[0])
	{
		print_export();
		return ;
	}
	export_helper(args);
}
