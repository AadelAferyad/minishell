/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:45:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/26 15:25:04 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

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
	if (!tmp)
	{
		g_structs.env = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
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
