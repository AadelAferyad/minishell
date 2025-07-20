/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:45:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/20 20:45:38 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	**get_env(void)
{
	static t_env	*head;
	static int		init;

	if (!init)
	{
		head = NULL;
		init = 1;
	}
	return (&head);
}

static void	trim(t_env *node)
{
	t_env	*tmp;
	t_env	**head;

	head = get_env();
	tmp = *head;
	node->next = NULL;
	if (!(*head))
	{
		*head = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	list_len(void)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *get_env();
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**create_env_arr(void)
{
	char	**arr;
	char	*buff;
	t_env	*tmp;
	int		i;

	tmp = *get_env();
	arr = safe_malloc(sizeof(char *) * (list_len() + 1));
	i = 0;
	while (tmp)
	{
		buff = ft_strjoin(tmp->key, "=");
		arr[i] = ft_strjoin(buff, tmp->value);
		free_collector_one(buff);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	create_env(char **env)
{
	int		i;
	int		j;
	t_env	*node;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		node = malloc(sizeof(t_env));
		node->key = _substr(env[i], 0, j);
		node->value = _substr(env[i], j + 1, ft_strlen(&env[i][j]));
		if (!node || !node->key || !node->value)
		{
			free_collector_all(0);
			exit(1);
		}
		trim(node);
		i++;
	}
}
