/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:03:16 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/22 10:42:12 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <fcntl.h>


int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) env;
	/*fd = open("file", O_RDWR | O_CREAT, S_IRWXU);*/
	/*if (fd == -1)*/
	/*	return (1);*/

	builtin_pwd(1);
	builtin_cd(av[1]);
	builtin_pwd(1);
	return (0);
}
