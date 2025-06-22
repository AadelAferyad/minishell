/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:03:54 by imellali          #+#    #+#             */
/*   Updated: 2025/06/22 14:14:47 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * class_tokens - it classify the raw string to its corresponding type
 * 
 * @tokens: pointer to tokens list
 * 
 * return: nothing
 */

static void	class_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->value, "|") == 1)
			tokens->type = PIPE;
		else if (ft_strcmp(tokens->value, "<") == 1)
			tokens->type = R_IN;
		else if (ft_strcmp(tokens->value, ">") == 1)
			tokens->type = R_OUT;
		else if (ft_strcmp(tokens->value, ">>") == 1)
			tokens->type = R_APPEND;
		else if (ft_strcmp(tokens->value, "<<") == 1)
			tokens->type = R_HEREDOC;
		else
			tokens->type = WORD;
		tokens = tokens->next;
	}
}
/**
 * lexer - split the input string into tokens and classifying it
 *
 * @input: the user input which is the command passed by user 
 * 
 * return: list that contain splitted tokens , NULL if failed
 */

t_tokens	*lexer(char *input)
{
	t_tokens	*tokens;
	int			i;
	int			start;
	char		*word;
	char		*operator;

	tokens = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i + 1] && ft_isdouble_op(input + i))
		{
			operator = ft_substr(input, i, 2);
			if (!operator)
				return (NULL);
			tokens = create_token(tokens, operator);
			if (!tokens)
			{
				free(operator);
				free_list(&tokens);
				return (NULL);
			}
			free(operator);
			i += 2;
			continue ;
		}
		if (ft_isop(input[i]))
		{
			operator = ft_substr(input, i, 1);
			if (!operator)
				return (NULL);
			tokens = create_token(tokens, operator);
			if (!tokens)
			{
				free(operator);
				free_list(&tokens);
				return (NULL);
			}
			free(operator);
			i++;
			continue ;
		}
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		start = i;
		while (input[i] && !ft_isop(input[i]) && !ft_isspace(input[i]))
			i++;
		word = ft_substr(input, start, i - start);
		if (!word)
		{
			free_list(&tokens);
			return (NULL);
		}
		tokens = create_token(tokens, word);
		if (!tokens)
		{
			free(word);
			free_list(&tokens);
			return (NULL);
		}
		free(word);
	}
	class_tokens(tokens);
	return (tokens);
}
