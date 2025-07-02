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
	/*t_cmd	*t;*/
	t_pipe	ptr;

	ptr.prev_pipe = -1;
	g_structs.collector = NULL;
	g_structs.env = NULL;
	g_structs.cmd = NULL;
	g_structs._pipe = &ptr;

	create_env(env);

	/*t = safe_malloc(sizeof(t_cmd));*/
	/*t->next = NULL;*/
	/*t->args = safe_malloc(sizeof(char *) * 5);*/
	/*t->args[0] = ft_strdup("wc");*/
	/*t->args[1] = ft_strdup("-l");*/
	/*t->args[2] = NULL;*/
	/*t->reds = NULL;*/

	n = safe_malloc(sizeof(t_cmd));
	n->next = NULL;
	n->args = safe_malloc(sizeof(char *) * 5);
	n->args[0] = ft_strdup("cat");
	n->args[1] = NULL;
	n->reds = NULL;

	cmd = safe_malloc(sizeof(t_cmd));
	cmd->next = n;

	cmd->args = safe_malloc(sizeof(char *) * 5);
	cmd->args[0] = ft_strdup("ls");
	cmd->args[1] = NULL;
	cmd->reds = NULL;
	g_structs.cmd = cmd;
	/*cmd->reds = safe_malloc(sizeof(t_reds));*/
	/*cmd->reds->type = R_OUT;*/
	/*cmd->reds->flag = "l";*/
	/*cmd->reds->next =NULL;*/

	(void) ac;
	(void) av;
	execution();
	free_collector_all();	
	return (0);
}
