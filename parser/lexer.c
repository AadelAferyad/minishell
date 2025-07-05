/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:03:54 by imellali          #+#    #+#             */
/*   Updated: 2025/07/02 17:06:17 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tokens	*cleanup(void)
{
	free_collector_all();
	return (NULL);
}

static int	lexer_helper_op(char *input, int *i, t_tokens **tokens)
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

/**
 * class_tokens - it classify the raw string to its corresponding type
 * 
 * @tokens: pointer to tokens list
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

static t_tokens	*cleanup(void)
{
	free_collector_all(1);
	return (NULL);
}

/**
 * lexer - split the input string into tokens and classifying it
 *
 * @input: the user input which is the command passed by user 
 * 
 * Return: list that contain splitted tokens , NULL if failed
 */

t_tokens	*lexer(char *input)
{
	t_tokens	*tokens;
	int			i;
	int			flag;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		flag = lexer_helper_op(input, &i, &tokens);
		if (flag == 1)
			continue ;
		if (flag == -1)
			return (cleanup());
		if (handle_space(input, &i))
			continue ;
		flag = handle_word(input, &i, &tokens);
		if (flag == 1)
			continue ;
		if (flag == -1)
			return (cleanup());
	}
	class_tokens(tokens);
	return (tokens);
}
