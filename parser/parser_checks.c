/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 01:53:21 by imellali          #+#    #+#             */
/*   Updated: 2025/06/29 05:48:28 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_redir_type(char *token)
{
	if (!token)
		return (-1);
	if (ft_strcmp(token, "<") == 1)
		return (R_IN);
	if (ft_strcmp(token, ">") == 1)
		return (R_OUT);
	if (ft_strcmp(token, ">>") == 1)
		return (R_APPEND);
	if (ft_strcmp(token, "<<") == 1)
		return (R_HEREDOC);
	return (-1);
}

void	syntax_error(char *token)
{
	ft_putstr_fd("syntax error near unexpected token : '", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

int	is_pipe(char *token)
{
	if (token && ft_strcmp(token, "|") == 1)
		return (1);
	return (0);
}

int	double_pipe(t_tokens *current)
{
	if (current && is_pipe(current->value) && current->next
		&& is_pipe(current->next->value))
	{
		syntax_error("|");
		return (-1);
	}
	return (0);
}

int	pipe_error(t_tokens *current)
{
	if (current && is_pipe(current->value))
	{
		syntax_error("|");
		return (-1);
	}
	return (0);
}
