/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:16:13 by imellali          #+#    #+#             */
/*   Updated: 2025/07/19 16:05:08 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	is_quoted_seg(t_segment *segments)
{
	t_segment	*cur;

	cur = segments;
	while (cur)
	{
		if (cur->q_type == Q_SINGLE || cur->q_type == Q_DOUBLE)
			return (1);
		cur = cur->next;
	}
	return (0);
}

char	*extract_quoted(char *input, int *i, char quote)
{
	int		start;
	int		end;
	char	*word;

	start = *i + 1;
	end = start;
	while (input[end] && input[end] != quote)
		end++;
	if (input[end] != quote)
	{
		ft_putstr_fd("Parser error : Enclosed Quotes!\n", 2);
		return (NULL);
	}
	word = extracting_word(input, start, end);
	if (!word)
		return (NULL);
	*i = end + 1;
	return (word);
}

int	handle_quoted(char *input, int *i, t_segment **segments, int qtype)
{
	char		*tmp;
	t_segment	*new_seg;

	tmp = extract_quoted(input, i, input[*i]);
	if (!tmp)
		return (-1);
	new_seg = safe_malloc(sizeof(t_segment));
	if (!new_seg)
		return (free_collector_one(tmp), -1);
	new_seg->value = tmp;
	new_seg->q_type = qtype;
	new_seg->next = NULL;
	add_seg(segments, new_seg);
	return (0);
}

void	handle_unquoted(char *input, int *i, t_segment **segments)
{
	int			start;
	int			end;
	char		*tmp;
	t_segment	*new_seg;

	start = *i;
	end = start;
	while (input[end] && !ft_isspace(input[end]) && !ft_isop(input[end])
		&& input[end] != '\'' && input[end] != '"')
		end++;
	if (end == start)
		return ;
	tmp = extracting_word(input, start, end);
	if (!tmp)
		return ;
	new_seg = safe_malloc(sizeof(t_segment));
	if (!new_seg)
		return (free_collector_one(tmp));
	new_seg->value = tmp;
	new_seg->q_type = Q_NONE;
	new_seg->next = NULL;
	add_seg(segments, new_seg);
	*i = end;
}
