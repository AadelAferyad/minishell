/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:15:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/26 15:23:42 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <readline/readline.h>

t_global	g_structs;

int	main(int ac, char **av, char **env)
{

	char	*buffer;
	g_structs.collector = NULL;
	g_structs.env = NULL;

	(void) ac;
	create_env(env);
	while ((buffer = readline("$shell: ")))
	{
		if (strncmp(buffer, "cd", 2) == 0)
		{

			/*
			 * cd dsadsa
			 * */
			if (!buffer[2])
				continue;
			builtin_cd(buffer + 3);
		}
		else if (strncmp(buffer, "pwd", 3) == 0)
			builtin_pwd(1);
		else if (strncmp(buffer, "env", 3) == 0)
			builtin_env(1);
		else
			ft_putstr_fd("unknown cmd\n", 1);

	}
	builtin_echo(av[1], 1)
	ft_putstr_fd("Exiting shell\n", 1);
	free_collector_all();	
	return (0);
}
