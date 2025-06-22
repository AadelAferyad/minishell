/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:16:13 by imellali          #+#    #+#             */
/*   Updated: 2025/06/22 18:46:42 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_double_qt(char *input, int *i, t_tokens **tokens)
{
	int		start;
	int		end;
	char	*word;

	start = *i + 1;
	end = start;
	while (input[end] && input[end] != '"')
		end++;
	if (input[end] != '"')
		return (-1);
	word = ft_substr(input, start, end - start);
	if (!word)
	{
		free_list(tokens);
		return (-1);
	}
	*tokens = create_token(*tokens, word, Q_DOUBLE);
	if (!*tokens)
	{
		free(word);
		free_list(tokens);
		return (-1);
	}
	*i = end + 1;
	free(word);
	return (1);
}

int	handle_single_qt(char *input, int *i, t_tokens **tokens)
{
	int		start;
	int		end;
	char	*word;

	start = *i + 1;
	end = start;
	while (input[end] && input[end] != '\'')
		end++;
	if (input[end] != '\'')
		return (-1);
	word = ft_substr(input, start, end - start);
	if (!word)
	{
		free_list(tokens);
		return (-1);
	}
	*tokens = create_token(*tokens, word, Q_SINGLE);
	if (!*tokens)
	{
		free(word);
		free_list(tokens);
		return (-1);
	}
	*i = end + 1;
	free(word);
	return (1);
}
