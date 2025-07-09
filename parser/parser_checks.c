/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 01:53:21 by imellali          #+#    #+#             */
/*   Updated: 2025/07/09 12:08:38 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	syntax_error(char *token)
{
	ft_putstr_fd("syntax error unexpected token : ", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

int	double_pipe(t_tokens *current)
{
	if (current && current->type == PIPE && current->next
		&& current->next->type == PIPE)
	{
		syntax_error("|");
		return (-1);
	}
	return (0);
}

int	pipe_error(t_tokens *current)
{
	if (current && current->type == PIPE)
	{
		syntax_error("|");
		return (-1);
	}
	return (0);
}

int	is_redir(int type)
{
	return (type == R_IN || type == R_OUT || type == R_APPEND
		|| type == R_HEREDOC);
}

int	is_word(int type)
{
	return (type == WORD);
}
