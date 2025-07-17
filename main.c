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

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	*buff;
	t_tokens	*lex;
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);
	g_structs.collector = NULL;
	g_structs.cmd = NULL;
	(void) ac;
	(void) av;
	create_env(env);
	while ((buff = readline("lgzara: ")))
	{
		if (ft_strlen(buff) != 0)
			add_history(buff);
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
