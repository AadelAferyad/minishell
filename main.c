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
	char	*buff;
	char	**grid;
	t_cmd	*cmd;
	g_structs.collector = NULL;
	g_structs.env = NULL;
	g_structs.cmd = NULL;
	g_structs._pipe = NULL;

	while ((buff = readline("samawi : ")))
	{
		grid = ft_split(buff, ' ');
		for (int i = 0; grid[i]; i++)
		{
			cmd = safe_malloc(sizeof(t_cmd));
			cmd = 
		}
	}
	create_env(env);
}
