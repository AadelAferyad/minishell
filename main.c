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
	t_cmd	*n;
	g_structs.collector = NULL;
	g_structs.env = NULL;
	g_structs.cmd = NULL;

	create_env(env);

	ft_putstr_fd(av[2], 1);

	n = safe_malloc(sizeof(t_cmd));
	n->next = NULL;
	n->args = safe_malloc(sizeof(char *) * 5);
	n->args[0] = ft_strdup(av[2]);
	n->args[1] = NULL;
	n->reds = NULL;

	g_structs.cmd = safe_malloc(sizeof(t_cmd));
	cmd = g_structs.cmd;
	cmd->next = n;

	cmd->args = safe_malloc(sizeof(char *) * 5);
	cmd->args[0] = ft_strdup(av[1]);
	cmd->args[1] = NULL;
	cmd->reds = NULL;
	/*cmd->reds = safe_malloc(sizeof(t_reds));*/
	/*cmd->reds->type = R_OUT;*/
	/*cmd->reds->flag = "l";*/
	/*cmd->reds->next =NULL;*/

	(void) ac;
	execution();
	free_collector_all();	
	return (0);
}
