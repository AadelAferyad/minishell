/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:43:10 by imellali          #+#    #+#             */
/*   Updated: 2025/06/25 16:06:42 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * handle_double_op - Handles double character operators in the input string
 * 
 * @input: The input string to be tokenized
 * @i: Pointer to the current position in the input string
 * @tokens: Double pointer to the list of tokens to be updated
 *
 * Return: 1 if a double operator was handled, 0 if not
 * 			-1 on error
 */

int	handle_double_op(char *input, int *i, t_tokens **tokens)
{
	char	*operator;

	if (input[*i + 1] && ft_isdouble_op(input + *i))
	{
		operator = safe_substr(input, *i, 2);
		if (!operator)
			return (-1);
		*tokens = create_token(*tokens, operator, Q_NONE);
		if (!*tokens)
		{
			free_collector_one(operator);
			free_collector_all();
			return (-1);
		}
		free_collector_one(operator);
		*i += 2;
		return (1);
	}
	return (0);
}
/**
 * handle_single_op - Handles single character operators in the input string
 * @input: The input string to be tokenized
 * @i: Pointer to the current position in the input string
 * @tokens: Double pointer to the list of tokens to be updated
 * 
 * Return: 1 if a single operator was handled, 0 if not
 * 			-1 on error
 */

int	handle_single_op(char *input, int *i, t_tokens **tokens)
{
	char	*operator;

	if (ft_isop(input[*i]))
	{
		operator = safe_substr(input, *i, 1);
		if (!operator)
			return (-1);
		*tokens = create_token(*tokens, operator, Q_NONE);
		if (!*tokens)
		{
			free_collector_one(operator);
			free_collector_all();
			return (-1);
		}
		free_collector_one(operator);
		(*i)++;
		return (1);
	}
	return (0);
}

/**
 * handle_word - Handles word tokens in the input string
 * 
 * @input: The input string to be tokenized
 * @i: Pointer to the current position in the input string
 * @tokens: Double pointer to the list of tokens to be updated
 *
 * Return: 1 if a word was handled, 0 if not
 *         -1 on error
 */

int	handle_word(char *input, int *i, t_tokens **tokens)
{
	int		start;
	char	*word;

	start = *i;
	while (input[*i] && !ft_isop(input[*i]) && !ft_isspace(input[*i]))
		(*i)++;
	word = extracting_word(input, start, *i);
	if (!word)
		return (-1);
	*tokens = create_token(*tokens, word, Q_NONE);
	if (!*tokens)
	{
		free_collector_one(word);
		free_collector_all();
		return (-1);
	}
	free_collector_one(word);
	return (1);
}

/**
 * handle_space - Skips whitespace characters in the input string
 * 
 * @input: The input string to be tokenized
 * @i: Pointer to the current position in the input string
 *
 * Return: 1 if whitespace skipped, 0 if not
 */

int	handle_space(char *input, int *i)
{
	if (ft_isspace(input[*i]))
	{
		(*i)++;
		return (1);
	}
	return (0);
}
