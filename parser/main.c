/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:17:44 by imellali          #+#    #+#             */
/*   Updated: 2025/06/26 14:18:50 by imellali         ###   ########.fr       */
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

int	main(void)
{
	char		*input;
	t_tokens	*tokens;
	size_t		n;
	ssize_t		nread;

	n = 444;
	input = safe_malloc(sizeof(char) * n);
	if (!input)
		return (-1);
	nread = getline(&input, &n, stdin);
	if (nread == -1)
		return (-1);
	tokens = lexer(input);
	if (!tokens)
	{
		free_collector_all();
		return (-1);
	}
	print_tokens(tokens);
	free_collector_all();
	return (0);
}
