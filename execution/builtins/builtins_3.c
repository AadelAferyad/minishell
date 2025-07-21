/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:17:44 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/20 20:21:52 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_export(void)
{
	t_env	*tmp;

	tmp = *get_env();
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_structs.exit_status = 0;
}

t_env	*does_node_exists(char *key, int size)
{
	t_env	*node;

	node = *get_env();
	while (node)
	{
		if (!ft_strncmp(key, node->key, size))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	add_node_to_env(char *key, char *value)
{
	t_env	*node;
	t_env	**head;

	head = get_env();
	node = does_node_exists(key, ft_strlen(key));
	if (node)
	{
		free(node->value);
		node->value = _strdup(value);
	}
	else
	{
		node = create_node_env(key, value);
		node->next = *head;
		*head = node;
	}
}

t_env	*search_for_node(t_env **head, char *arg)
{
	int		size;
	t_env	*node;
	t_env	*tmp;

	node = *head;
	tmp = node;
	size = ft_strlen(arg);
	while (node)
	{
		if (!ft_strncmp(arg, node->key, size))
		{
			if (node == *head)
			{
				*head = node->next;
			}
			else
				tmp->next = node->next;
			return (free_node(node, NULL), tmp);
		}
		tmp = node;
		node = node->next;
	}
	return (NULL);
}

void	builtin_unset(char **args)
{
	t_env	**head;
	int		i;

	head = get_env();
	g_structs.exit_status = 0;
	if (!args || !args[0])
		return ;
	i = 0;
	while (args[i])
	{
		search_for_node(head, args[i]);
		i++;
	}
}
