/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:17:44 by imellali          #+#    #+#             */
/*   Updated: 2025/07/05 16:41:04 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_global	g_structs;

void	print_segments(t_segment *segments)
{
	int	i;

	i = 0;
	while (segments)
	{
		printf("    [segment]: value=%s, quote_type=%d\n\n",
			segments->value, segments->q_type);
		segments = segments->next;
		i++;
	}
}

static void	print_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("VALUE =  [%s]   TYPE = %u\n", tokens->value,
			tokens->type);
		print_segments(tokens->segments);
		tokens = tokens->next;
		i++;
	}
}

static void	print_reds(t_reds *reds)
{
	while (reds)
	{
		printf("    [redir] type: %d, flag: %s\n", reds->type, reds->flag);
		reds = reds->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds)
	{
		printf("Command #%d:\n", i++);
		if (cmds->args)
		{
			j = 0;
			while (cmds->args[j])
			{
				printf("  [arg %d]: %s\n", j, cmds->args[j]);
				j++;
			}
		}
		else
			printf("  [no args]\n");
		if (cmds->reds)
			print_reds(cmds->reds);
		else
			printf("  [no redirections]\n");
		cmds = cmds->next;
		printf("\n");
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(int argc, char **argv)
{
	char		*input;
	t_tokens	*tokens;
	t_cmd		*cmds;

	(void)argc;
	(void)argv;
	g_structs.env = NULL;
	// print_env(g_structs.env);
	input = readline("marvel$> ");
	if (!input)
		return (free_collector_all(1), -1);
	tokens = lexer(input);
	if (!tokens)
		return (free_collector_all(1), -1);
	print_tokens(tokens);
	cmds = parse_tokens(tokens);
	if (!cmds)
		return (free_collector_all(1), -1);
	print_cmds(cmds);
	free_collector_all(1);
	return (0);
}
