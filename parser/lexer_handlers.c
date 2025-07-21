/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:43:10 by imellali          #+#    #+#             */
/*   Updated: 2025/07/19 16:05:09 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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
		operator = ft_substr(input, *i, 2);
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
		operator = ft_substr(input, *i, 1);
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

/**
 * handle_segs - Handles the splitting and tokenization of segments
 * 
 * @tokens: Double pointer to the list of tokens to be updated
 * @segments: Pointer to the list of segments to be processed
 * 
 * Return: 0 on success, -1 on error
 */
int	handle_segs(t_tokens **tokens, t_segment *segments)
{
	char	*joined;
	char	**field;

	if (!segments)
		return (-1);
	joined = join_segs(segments);
	if (!joined)
		return (-1);
	if (is_quoted_seg(segments))
	{
		if (add_fields(tokens, (char *[]){joined, NULL}, joined) == -1)
			return (free_collector_one(joined), -1);
	}
	else
	{
		field = field_splitting(joined);
		if (add_fields(tokens, field, joined) == -1)
			return (free_collector_one(joined), free_fields(field), -1);
		free_fields(field);
	}
	free_collector_one(joined);
	return (0);
}

static int	handle_word_loop(char *input, int *i, t_segment **segments)
{
	while (input[*i] && !ft_isspace(input[*i]) && !ft_isop(input[*i]))
	{
		if (input[*i] == '\'')
		{
			if (handle_quoted(input, i, segments, Q_SINGLE) == -1)
				return (-1);
		}
		else if (input[*i] == '"')
		{
			if (handle_quoted(input, i, segments, Q_DOUBLE) == -1)
				return (-1);
		}
		else
			handle_unquoted(input, i, segments);
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
int	handle_word(char *input, int *i, t_tokens **tokens, int is_heredoc_del)
{
	t_segment	*segments;
	int			status;

	segments = NULL;
	status = handle_word_loop(input, i, &segments);
	if (status == -1)
		return (-1);
	if (segments)
	{
		if (is_heredoc_del)
			return (create_seg_token(tokens, segments));
		else
			return (handle_segs(tokens, segments));
	}
	return (0);
}
