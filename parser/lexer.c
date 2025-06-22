/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:03:54 by imellali          #+#    #+#             */
/*   Updated: 2025/06/22 14:45:11 by imellali         ###   ########.fr       */
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

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (handle_double_op(input, &i, &tokens) == 1)
			continue ;
		if (handle_double_op(input, &i, &tokens) == -1)
			return (NULL);
		if (handle_single_op(input, &i, &tokens) == 1)
			continue ;
		if (handle_single_op(input, &i, &tokens) == -1)
			return (NULL);
		if (handle_space(input, &i))
			continue ;
		if (handle_word(input, &i, &tokens) == -1)
			return (NULL);
	}
	class_tokens(tokens);
	return (tokens);
}
