/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:03:54 by imellali          #+#    #+#             */
/*   Updated: 2025/07/20 22:42:16 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	handle_assignment(char *input, int *i, t_tokens **tokens)
{
	int		start;
	int		name_end;
	int		value_start;
	char	*name_token;

	start = *i;
	name_end = start;
	(void) tokens;
	while (input[name_end] && is_valid_char(input[name_end]))
		name_end++;
	if (input[name_end] == '=')
	{
		if (!is_valid_start(input[start]))
			return (ft_putstr_fd("not a valid identifier\n", 2),
				g_structs.exit_status = 1, -1);
		name_token = extracting_word(input, start, name_end + 1);
		*tokens = create_token(*tokens, name_token);
		free_collector_one(name_token);
		value_start = name_end + 1;
		if (input[value_start] == '"' || input[value_start] == '\'')
			return (handle_export_quoted(input, i, value_start, tokens));
		else
			return (handle_export_unquoted(input, i, value_start, tokens));
	}
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

int	handle_op_and_heredoc(char *input, int *i, t_tokens **tokens, int *heredoc)
{
	int	flag;

	flag = lexer_helper_op(input, i, tokens);
	if (flag == 1)
	{
		*heredoc = update_heredoc_flag(*tokens);
		return (1);
	}
	if (flag == -1)
		return (-1);
	return (0);
}

int	lexer_loop(char *input, int *i, t_tokens **tokens, int *heredoc)
{
	int	ret;

	while (input[*i])
	{
		ret = handle_op_and_heredoc(input, i, tokens, heredoc);
		if (ret == 1)
			continue ;
		if (ret == -1)
			return (-1);
		if (handle_space(input, i))
			continue ;
		ret = handle_export_and_word(input, i, tokens, heredoc);
		if (ret == 1)
			continue ;
		if (ret == -1)
			return (-1);
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
	int			heredoc;
	int			status;

	tokens = NULL;
	i = 0;
	heredoc = 0;
	status = lexer_loop(input, &i, &tokens, &heredoc);
	if (status == -1)
		return (lexer_cleanup());
	class_tokens(tokens);
	return (tokens);
}
