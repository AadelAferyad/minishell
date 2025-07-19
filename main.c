/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:15:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/19 18:09:50 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <minishell.h>
#include <parser.h>

t_global	g_structs;

void	signal_handler(int sig)
{
	(void) sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_structs.exit_status = 130;
}

int	main(int ac, char **av, char **env)
{
	char	*buff;
	t_tokens	*lex;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	g_structs.collector = NULL;
	g_structs.cmd = NULL;
	g_structs.exit_status = 0;
	(void) ac;
	(void) av;
	create_env(env);
	while ((buff = readline("lgzara: ")))
	{
		if (ft_strlen(buff) != 0)
			add_history(buff);
		lex = lexer(buff);
		free(buff);
		if (!lex)
		{
			free_collector_all(1);
			continue ;
		}
		g_structs.cmd = parse_tokens(lex);	
		execution();
		free_collector_all(1);
	}
	free_collector_all(0);
	return (0);
}
