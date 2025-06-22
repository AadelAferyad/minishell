/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:18:31 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/21 14:09:38 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <fcntl.h>


int	main(int ac, char **av, char **env)
{
	int	fd;

	fd = 1;
	fd = open("file", O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1)
		return (1);
	builtin_pwd(1);

	return (0);
}
 
