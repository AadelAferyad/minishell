/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:54:43 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/20 20:18:00 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_pwd(char *s, t_env **head, char *buff)
{
	t_env	*node;

	node = create_node_env(s, buff);
	node->next = *head;
	(*head) = node;
	free(buff);
}

static int	export_check(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

static int	check_args(char *args)
{
	int	j;

	j = 0;
	while (args[j] && args[j] != '=')
	{
		if (ft_isdigit(args[0]) || !export_check(args[j]))
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			g_structs.exit_status = 1;
			return (-1);
		}
		j++;
	}
	return (j);
}

static void	add_nodes_elper(char *key, char *value, int *i, int n)
{
	*i = *i + n;
	add_node_to_env(key, value);
	free_collector_one(key);
	free_collector_one(value);
	g_structs.exit_status = 0;
}

void	export_helper(char **args)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	while (args[i])
	{
		j = check_args(args[i]);
		if (j == -1)
			return ;
		if (!args[i][j])
		{
			key = ft_substr(args[i], 0, j);
			value = ft_strdup("");
			add_nodes_elper(key, value, &i, 1);
			continue ;
		}
		key = ft_substr(args[i], 0, j);
		if (!args[i + 1])
			value = ft_strdup("");
		else
			value = ft_strdup(args[i + 1]);
		add_nodes_elper(key, value, &i, 2);
	}
}
