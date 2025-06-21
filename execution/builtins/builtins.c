/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:46:07 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/21 13:58:16 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	builtin_echo(char **arg, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (arg[i][0] == '-' && arg[i][1] == 'n' && arg[i][2] == '\0')
	{
		flag = 1;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd);
		i++;
		if (arg[i])
			ft_putchar_fd(' ', fd);
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
