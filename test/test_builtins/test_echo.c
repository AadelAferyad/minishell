/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:42:54 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/21 19:01:28 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <fcntl.h>


int	main(int ac, char **av, char **env)
{
	int	fd;
	(void) ac;
	(void) env;
	fd = 1;
	fd = open("file", O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1)
		return (1);
	builtin_echo(&av[2], 1);
	builtin_echo(&av[2], fd);
	close(fd);

	return (0);
}
 
