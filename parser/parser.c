/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:10:43 by imellali          #+#    #+#             */
/*   Updated: 2025/06/29 05:44:48 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_args(t_tokens *current)
{
	int	count;

	count = 0;
	while (current && !is_pipe(current->value))
	{
		if (get_redir_type(current->value) != -1)
		{
			if (!current->next || is_pipe(current->next->value))
				return (count);
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

static t_cmd	*parse_one(t_tokens **current)
{
	t_cmd		*cmd;
	t_tokens	*cur;
	int			arg_count;
	int			i;
	int			redir_type;

	cur = *current;
	arg_count = count_args(cur);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
	{
		free_collector_one(cmd);
		return (NULL);
	}
	cur = *current;
	i = 0;
	while (cur && !is_pipe(cur->value))
	{
		redir_type = get_redir_type(cur->value);
		if (redir_type != -1)
		{
			if (!cur->next || is_pipe(cur->next->value))
			{
				syntax_error("newline");
				free_collector_one(cmd);
				return (NULL);
			}
			cmd->reds = add_redir(cmd->reds, redir_type, cur->next->value);
			cur = cur->next->next;
		}
		else
		{
			if (i < arg_count)
				cmd->args[i++] = ft_strdup(cur->value);
			cur = cur->next;
		}
	}
	cmd->args[i] = NULL;
	*current = cur;
	return (cmd);
}

static int	parse_loop(t_tokens *current, int *last_pipe, t_cmd **pipeline)
{
	t_cmd	*cmd;

	*last_pipe = 0;
	while (current)
	{
		if (pipe_error(current) == -1)
			return (free_collector_all(), -1);
		cmd = parse_one(&current);
		if (!cmd)
			return (free_collector_all(), -1);
		if (double_pipe(current) == -1)
			return (free_collector_all(), -1);
		*pipeline = add_cmd(*pipeline, cmd);
		if (current && is_pipe(current->value))
		{
			current = current->next;
			*last_pipe = 1;
		}
		else
			*last_pipe = 0;
	}
	return (0);
}

t_cmd	*parse_tokens(t_tokens *tokens)
{
	int		last_pipe;
	t_cmd	*pipeline;

	last_pipe = 0;
	pipeline = NULL;
	if (tokens && is_pipe(tokens->value))
		return (syntax_error("|"), NULL);
	if (parse_loop(tokens, &last_pipe, &pipeline) == -1)
		return (NULL);
	if (last_pipe)
		return (syntax_error("|"), free_collector_all(), NULL);
	return (pipeline);
}
