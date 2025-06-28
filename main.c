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
	t_cmd	*cmd;
	g_structs.collector = NULL;
	g_structs.env = NULL;
	g_structs.cmd = NULL;

	create_env(env);
	g_structs.cmd = safe_malloc(sizeof(t_cmd));
	cmd = g_structs.cmd;
	cmd->next = NULL;

	cmd->args = safe_malloc(sizeof(char *) * 5);
	cmd->args[0] = ft_strdup("libft/");
	cmd->args[1] = ft_strdup("..");
	cmd->args[2] = NULL;
	(void) ac;
	(void) av;
	execution();
	free_collector_all();	
	return (0);
}
