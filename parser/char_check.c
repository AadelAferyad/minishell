/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:58:36 by imellali          #+#    #+#             */
/*   Updated: 2025/07/09 12:06:40 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	redir_error(t_tokens *cur)
{
	while (cur && cur->type != PIPE)
	{
		if (is_redir(cur->type) && (!cur->next || !is_word(cur->next->type)))
		{
			if (cur->next)
				syntax_error(cur->next->value);
			else
				syntax_error("newline");
			break ;
		}
		cur = cur->next;
	}
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

int	ft_isop(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_isdouble_op(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return (1);
	else if (input[0] == '>' && input[1] == '>')
		return (1);
	return (0);
}

int	handle_space(char *input, int *i)
{
	if (ft_isspace(input[*i]))
	{
		(*i)++;
		return (1);
	}
	return (0);
}
