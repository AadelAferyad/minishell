/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:17:44 by imellali          #+#    #+#             */
/*   Updated: 2025/06/29 05:44:03 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_global	g_structs;

static void	print_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("VALUE =  [%s]   TYPE = %u   QUOTE_TYPE = %u\n", tokens->value,
			tokens->type, tokens->quote_type);
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
	}
}

int	main(void)
{
	char		*input;
	t_tokens	*tokens;
	t_cmd		*cmds;
	size_t		n;
	ssize_t		nread;

	n = 444;
	input = safe_malloc(sizeof(char) * n);
	if (!input)
		return (-1);
	nread = getline(&input, &n, stdin);
	if (nread == -1)
	{
		free_collector_all();
		return (-1);
	}
	tokens = lexer(input);
	if (!tokens)
	{
		free_collector_all();
		return (-1);
	}
	print_tokens(tokens);
	cmds = parse_tokens(tokens);
	if (!cmds)
	{
		free_collector_all();
		return (-1);
	}
	print_cmds(cmds);
	free_collector_all();
	return (0);
}
