/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:15:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/09 12:50:45 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <minishell.h>
#include <parser.h>

t_global	g_structs;

int	main(int ac, char **av, char **env)
{
	char	*buff;
	t_tokens	*lex;
	g_structs.collector = NULL;
	g_structs.cmd = NULL;

	(void) ac;
	(void) av;

	/*t_env	*head;*/
	create_env(env);
	/*head = *get_env();*/
	/*while (head)*/
	/*{*/
	/*	printf("%s=%s\n", head->key, head->value);*/
	/*	head = head->next;*/
	/*}*/
	while ((buff = readline("lgzara: ")))
	{
		if (ft_strlen(buff) != 0)
			add_history(buff);
		if (ft_strncmp("exit", buff, 5) == 0)
		{
			free_collector_all(0);
			free(buff);
			exit(0);
		}
		lex = lexer(buff);
		if (!lex)
		{
			free_collector_all(1);
			continue ;
		}
		g_structs.cmd = parse_tokens(lex);	
		execution();
		free(buff);
		free_collector_all(1);
	}
	free_collector_all(0);
	return (0);
}
