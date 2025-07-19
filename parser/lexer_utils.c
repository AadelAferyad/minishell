/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:45:34 by imellali          #+#    #+#             */
/*   Updated: 2025/07/19 16:05:11 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	lexer_helper_op(char *input, int *i, t_tokens **tokens)
{
	int	flag;

	flag = handle_double_op(input, i, tokens);
	if (flag == 1)
		return (1);
	if (flag == -1)
		return (-1);
	flag = handle_single_op(input, i, tokens);
	if (flag == 1)
		return (1);
	if (flag == -1)
		return (-1);
	return (0);
}

int	handle_export_and_word(char *input, int *i, t_tokens **tokens,
	int *heredoc)
{
	int	flag;

	flag = handle_assignment(input, i, tokens);
	if (flag == 1)
		return (1);
	if (flag == -1)
		return (-1);
	flag = handle_word(input, i, tokens, *heredoc);
	*heredoc = 0;
	if (flag == 1)
		return (1);
	if (flag == -1)
		return (-1);
	return (0);
}

int	handle_export_quoted(char *input, int *i, int start,
		t_tokens **tokens)
{
	char	quote;
	int		value_end;
	char	*value_token;

	quote = input[start];
	value_end = start + 1;
	while (input[value_end] && input[value_end] != quote)
		value_end++;
	if (!input[value_end])
	{
		ft_putstr_fd("Parser error : Enclosed Quotes!\n", 2);
		*i = value_end;
		return (-1);
	}
	value_token = extracting_word(input, start + 1, value_end);
	*tokens = create_token(*tokens, value_token);
	free_collector_one(value_token);
	if (input[value_end] == quote)
		value_end++;
	*i = value_end;
	return (1);
}

int	handle_export_unquoted(char *input, int *i, int start,
		t_tokens **tokens)
{
	int		value_end;
	char	*value_token;

	value_end = start;
	while (input[value_end] && !ft_isspace(input[value_end])
		&& !ft_isop(input[value_end]))
		value_end++;
	value_token = extracting_word(input, start, value_end);
	*tokens = create_token(*tokens, value_token);
	free_collector_one(value_token);
	*i = value_end;
	return (1);
}

int	update_heredoc_flag(t_tokens *tokens)
{
	t_tokens	*last;

	last = tokens;
	while (last && last->next)
		last = last->next;
	if (last && last->value && ft_strcmp(last->value, "<<") == 1)
		return (1);
	return (0);
}
