/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:38 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/20 20:30:52 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	printer(char **args, int i, int flag)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}

int	builtin_echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!args[0])
	{
		ft_putchar_fd('\n', 1);
		g_structs.exit_status = 0;
		return (0);
	}
	while (args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
	{
		flag = 1;
		i++;
	}
	printer(args, i, flag);
	g_structs.exit_status = 0;
	return (0);
}

void	free_node(t_env *node, char *buff)
{
	if (buff)
		free(buff);
	free(node->key);
	free(node->value);
	free(node);
}
