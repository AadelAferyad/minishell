/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:17:44 by imellali          #+#    #+#             */
/*   Updated: 2025/06/21 13:24:53 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isspace(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	ft_isop(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
/**
 * lexer - split the input string into tokens
 *
 * @input: the user input which is the command passed by user 
 * 
 * return: list that contain splitted tokens
 */

t_tokens	lexer(char *input)
{
	t_tokens	*tokens;
	int			i;
	int			start;
	char		*word;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		/* handling double operator */
		if (input[i + 1])
		{
			if (ft_isop(input[i]) == 1 && ft_isop(input[i + 1]) == 1)
			{
				add_token();
				i += 2;
				continue ;
			}
		}
		/* handling single operator */
		if (ft_isop(input[i]) == 1)
		{
			add_token();
			i++;
			continue ;
		}
		/* skipping spaces */
		if (ft_isspace(input[i]) == 1)
		{
			i++;
			continue ;
		}
		/* handling words */
		start = i;
		while (input[i] && !ft_isop(input[i]) && !ft_isspace(input[i]))
			i++;
		word = ft_substr(input, start, i);
		add_token();
		i++;
	}
}

int	main(void)
{
	char	*input;
	size_t	n;
	ssize_t	nread;

	n = 444;
	input = malloc(sizeof(char) * n);
	if (!input)
		return (-1);
	nread = getline(&input, &n, stdin);
	if (nread == -1)
		return (-1);
	printf("Command : %s\n", input);
	free(input);
	return (0);
}
