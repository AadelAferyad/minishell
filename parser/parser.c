/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:10:43 by imellali          #+#    #+#             */
/*   Updated: 2025/07/15 12:37:19 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	count_args(t_tokens *current)
{
	int	count;

	count = 0;
	while (current && current->type != PIPE)
	{
		if (is_redir(current->type))
		{
			if (!current->next || !is_word(current->next->type))
				return (-1);
			current = current->next->next;
		}
		else
		{
			count++;
			current = current->next;
		}
	}
	return (count);
}

/**
 * init_cmd - Initializes a command structure by filling its arguments and
 *            redirection fields from a token list
 * 
 * @cur: Pointer to the current position in the tokens list
 * @cmd: Pointer to the t_cmd struct to be filled
 * @count: Number of arguments to expect
 * @i: Pointer to the index for inserting arguments into cmd->args
 *
 * Return: 0 on success, -1 on error
 */
static int	init_cmd(t_tokens **cur, t_cmd *cmd, int count, int *i)
{
	while (*cur && (*cur)->type != PIPE)
	{
		if (is_redir((*cur)->type))
		{
			if (validate_redir_syntax(cur, cmd) == -1)
				return (-1);
			if ((*cur)->type == R_HEREDOC)
			{
				if (process_heredoc_redir((*cur)->next, &cmd->reds, cmd) == -1)
					return (-1);
			}
			else
				cmd->reds = add_redir(cmd->reds, (*cur)->type,
						(*cur)->next->value, 0);
			*cur = (*cur)->next->next;
		}
		else
		{
			if (*i < count)
				cmd->args[(*i)++] = ft_strdup((*cur)->value);
			*cur = (*cur)->next;
		}
	}
	return (0);
}

/**
 * parse_one - Parses a single command segment from a token list
 * 
 * @current: Pointer to the current position in the tokens list. Updated to
 *           point past the parsed command (to the next pipe or end)
 *
 * Return: Pointer to t_cmd structure, NULL on error
 */
static t_cmd	*parse_one(t_tokens **current)
{
	t_cmd		*cmd;
	t_tokens	*cur;
	int			count;
	int			i;

	cur = *current;
	i = 0;
	count = count_args(cur);
	if (count == -1)
		return (redir_error(cur), NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc(count + 1, sizeof(char *));
	if (!cmd->args)
	{
		free_collector_one(cmd);
		return (NULL);
	}
	if (init_cmd(&cur, cmd, count, &i) == -1)
		return (NULL);
	cmd->args[i] = NULL;
	*current = cur;
	return (cmd);
}

/**
 * parse_loop - Builds a pipeline of commands from a token list
 * 
 * @current: The current token in the input list
 * @last_pipe: Pointer to an int set to 1 if the last token was pipe
 * @pipeline: Address of a t_cmd pointer,
	serves as the head of the pipeline list
 *
 * Return: 0 on success, -1 on error
 */
static int	parse_loop(t_tokens *current, int *last_pipe, t_cmd **pipeline)
{
	t_cmd	*cmd;

	*last_pipe = 0;
	while (current)
	{
		if (pipe_error(current) == -1)
			return (free_collector_all(1), -1);
		cmd = parse_one(&current);
		if (!cmd)
			return (free_collector_all(1), -1);
		if (double_pipe(current) == -1)
			return (free_collector_all(1), -1);
		*pipeline = add_cmd(*pipeline, cmd);
		if (current && current->type == PIPE)
		{
			current = current->next;
			*last_pipe = 1;
		}
		else
			*last_pipe = 0;
	}
	return (0);
}

/**
 * parse_tokens - parsing token list into a pipeline of commands
 * 
 * @tokens: Pointer to the head of the tokens list to be parsed
 *
 * Return: Pointer to the head of the pipeline, NULL on error
 */
t_cmd	*parse_tokens(t_tokens *tokens)
{
	int		last_pipe;
	t_cmd	*pipeline;

	last_pipe = 0;
	pipeline = NULL;
	if (tokens && tokens->type == PIPE)
		return (syntax_error("|"), NULL);
	if (parse_loop(tokens, &last_pipe, &pipeline) == -1)
		return (NULL);
	if (last_pipe)
		return (syntax_error("|"), free_collector_all(1), NULL);
	return (pipeline);
}
