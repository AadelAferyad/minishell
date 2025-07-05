/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:45:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/05 16:31:46 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	trim(char *s)
{
	int	i;
	t_env	*node;
	t_env	*tmp;

	i = 0;
	tmp = g_structs.env;
	while (s[i] != '=')
		i++;
	node = safe_malloc(sizeof(t_env));
	node->key = ft_substr(s, 0, i);
	node->value = ft_substr(s, i + 1, ft_strlen(&s[i]));
	node->next = NULL;
	flag_env(node);
	flag_env(node->key);
	flag_env(node->value);
	if (!tmp)
	{
		g_structs.env = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	list_len()
{
	unsigned int	i;
	t_env	*tmp;

	i = 0;
	tmp = g_structs.env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**create_env_arr()
{
	char	**arr;
	char	*buff;
	t_env	*tmp;
	int	i;

	tmp = g_structs.env;
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
	int	i;

	i = 0;
	while (env[i])
	{
		trim(env[i]);
		i++;
	}
}
