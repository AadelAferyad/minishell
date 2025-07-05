/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:15:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/05 23:29:19 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <minishell.h>

t_global	g_structs;

int	main(int ac, char **av, char **env)
{
	char	*buff;
	t_tokens	*lex;
	g_structs.collector = NULL;
	g_structs.env = NULL;
	g_structs.cmd = NULL;

	(void) ac;
	(void) av;

	create_env(env);
	while ((buff = readline("lgzara: ")))
	{
		add_history(buff);
		if (ft_strncmp("exit", buff, 5) == 0)
			break ;
		lex = lexer(buff);
		if (!lex)
			continue ;
		g_structs.cmd = parse_tokens(lex);	
		execution();
		free_collector_all(1);
	}
	free(buff);
	free_collector_all(0);
	return (0);
}
