/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:03:54 by imellali          #+#    #+#             */
/*   Updated: 2025/07/15 13:21:48 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_tokens	*cleanup(void)
{
	free_collector_all(1);
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

void	class_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->value)
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
		}
		tokens = tokens->next;
	}
}

int	handle_assignment(char *input, int *i, t_tokens **tokens)
{
	int		start;
	int		name_end;
	int		value_start;
	int		value_end;
	char	quote;
	char	*name_token;
	char	*value_token;

	start = *i;
	name_end = start;
	while (input[name_end] && is_valid_char(input[name_end]))
		name_end++;
	if (input[name_end] == '=')
	{
		if (!is_valid_start(input[start]))
			return (ft_putstr_fd("not a valid identifier\n", 2), -1);
		name_token = extracting_word(input, start, name_end + 1);
		*tokens = create_token(*tokens, name_token);
		free_collector_one(name_token);
		value_start = name_end + 1;
		if (input[value_start] == '"' || input[value_start] == '\'')
		{
			quote = input[value_start];
			value_end = value_start + 1;
			while (input[value_end] && input[value_end] != quote)
				value_end++;
			if (!input[value_end])
			{
				ft_putstr_fd("Parser error : Enclosed Quotes!\n", 2);
				*i = value_end;
				return (-1);
			}
			value_token = extracting_word(input, value_start + 1, value_end);
			*tokens = create_token(*tokens, value_token);
			free_collector_one(value_token);
			if (input[value_end] == quote)
				value_end++;
			*i = value_end;
			return (1);
		}
		else
		{
			value_end = value_start;
			while (input[value_end] && !ft_isspace(input[value_end])
				&& !ft_isop(input[value_end]))
				value_end++;
			value_token = extracting_word(input, value_start, value_end);
			*tokens = create_token(*tokens, value_token);
			free_collector_one(value_token);
			*i = value_end;
			return (1);
		}
	}
	return (0);
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
	int			heredoc;
	t_tokens	*last;

	tokens = NULL;
	i = 0;
	heredoc = 0;
	while (input[i])
	{
		flag = lexer_helper_op(input, &i, &tokens);
		if (flag == 1)
		{
			last = tokens;
			while (last && last->next)
				last = last->next;
			if (last && last->value && ft_strcmp(last->value, "<<") == 1)
				heredoc = 1;
			continue ;
		}
		if (flag == -1)
			return (cleanup());
		if (handle_space(input, &i))
			continue ;
		flag = handle_assignment(input, &i, &tokens);
		if (flag == 1)
			continue ;
		if (flag == -1)
			return (cleanup());
		flag = handle_word(input, &i, &tokens, heredoc);
		heredoc = 0;
		if (flag == 1)
			continue ;
		if (flag == -1)
			return (cleanup());
	}
	class_tokens(tokens);
	return (tokens);
}
