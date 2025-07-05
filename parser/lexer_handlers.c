/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:43:10 by imellali          #+#    #+#             */
/*   Updated: 2025/07/05 23:22:51 by imellali         ###   ########.fr       */
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
		operator= ft_substr(input, *i, 2);
		if (!operator)
			return (-1);
		*tokens = create_token(*tokens, operator);
		if (!*tokens)
			return (free_collector_all(1), -1);
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
		operator= ft_substr(input, *i, 1);
		if (!operator)
			return (-1);
		*tokens = create_token(*tokens, operator);
		if (!*tokens)
		{
			free_collector_all(1);
			return (-1);
		}
		free_collector_one(operator);
		(*i)++;
		return (1);
	}
	return (0);
}

void	free_fields(char **fields)
{
	int	i;

	if (!fields)
		return ;
	i = 0;
	while (fields[i])
	{
		free_collector_one(fields[i]);
		i++;
	}
	free_collector_one(fields);
}

int	handle_segs(t_tokens **tokens, t_segment *segments)
{
	char	*expanded;
	char	**field;
	int		i;

	if (segments == NULL)
		return (-1);
	if (segments->next == NULL &&
		(segments->q_type == Q_SINGLE || segments->q_type == Q_DOUBLE))
		return (create_seg(tokens, segments));
	else
	{
		expanded = join_segs(segments);
		field = field_splitting(expanded);
		i = 0;
		while (field && field[i])
		{
			*tokens = create_token(*tokens, field[i]);
			if (!tokens)
			{
				free_collector_one(expanded);
				free_fields(field);
				return (-1);
			}
			i++;
		}
		free_collector_one(expanded);
		free_fields(field);
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
	t_segment	*segments;

	segments = NULL;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_isop(input[*i]))
	{
		if (input[*i] == '\'')
		{
			if (handle_quoted(input, i, &segments, Q_SINGLE) == -1)
				return (-1);
		}
		else if (input[*i] == '"')
		{
			if (handle_quoted(input, i, &segments, Q_DOUBLE) == -1)
				return (-1);
		}
		else
			handle_unquoted(input, i, &segments);
	}
	if (segments)
		return (handle_segs(tokens, segments));
	return (0);
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
