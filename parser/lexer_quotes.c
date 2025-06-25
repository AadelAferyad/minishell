/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:16:13 by imellali          #+#    #+#             */
/*   Updated: 2025/06/25 16:06:54 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	creating_token(char *word, t_tokens **tokens, t_qtypes qtype)
{
	*tokens = create_token(*tokens, word, qtype);
	if (!*tokens)
	{
		free_collector_one(word);
		free_collector_all();
		return (-1);
	}
	return (0);
}

static int	handle_quote(char *input, int *i, t_tokens **tokens, char quote)
{
	int			start;
	int			end;
	char		*word;
	t_qtypes	qtype;

	start = *i + 1;
	end = start;
	while (input[end] && input[end] != quote)
		end++;
	if (input[end] != quote)
		return (-1);
	word = extracting_word(input, start, end);
	if (!word)
		return (-1);
	if (quote == '"')
		qtype = Q_DOUBLE;
	else
		qtype = Q_SINGLE;
	if (creating_token(word, tokens, qtype) == -1)
		return (-1);
	*i = end + 1;
	free_collector_one(word);
	return (1);
}

int	handle_double_qt(char *input, int *i, t_tokens **tokens)
{
	return (handle_quote(input, i, tokens, '"'));
}

int	handle_single_qt(char *input, int *i, t_tokens **tokens)
{
	return (handle_quote(input, i, tokens, '\''));
}
