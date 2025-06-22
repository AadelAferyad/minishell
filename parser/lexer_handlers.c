/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:43:10 by imellali          #+#    #+#             */
/*   Updated: 2025/06/22 14:45:13 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_double_op(char *input, int *i, t_tokens **tokens)
{
	char	*operator;

	if (input[*i + 1] && ft_isdouble_op(input + *i))
	{
		operator = ft_substr(input, *i, 2);
		if (!operator)
			return (-1);
		*tokens = create_token(*tokens, operator);
		if (!*tokens)
		{
			free(operator);
			free_list(tokens);
			return (-1);
		}
		free(operator);
		*i += 2;
		return (1);
	}
	return (0);
}

int	handle_single_op(char *input, int *i, t_tokens **tokens)
{
	char	*operator;

	if (ft_isop(input[*i]))
	{
		operator = ft_substr(input, *i, 1);
		if (!operator)
			return (-1);
		*tokens = create_token(*tokens, operator);
		if (!*tokens)
		{
			free(operator);
			free_list(tokens);
			return (-1);
		}
		free(operator);
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_word(char *input, int *i, t_tokens **tokens)
{
	int		start;
	char	*word;

	start = *i;
	while (input[*i] && !ft_isop(input[*i]) && !ft_isspace(input[*i]))
		(*i)++;
	word = ft_substr(input, start, *i - start);
	if (!word)
	{
		free_list(tokens);
		return (-1);
	}
	*tokens = create_token(*tokens, word);
	if (!*tokens)
	{
		free(word);
		free_list(tokens);
		return (-1);
	}
	free(word);
	return (1);
}

int	handle_space(char *input, int *i)
{
	if (ft_isspace(input[*i]))
	{
		(*i)++;
		return (1);
	}
	return (0);
}
