/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:05:56 by imellali          #+#    #+#             */
/*   Updated: 2025/07/19 16:05:10 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	add_seg(t_segment **head, t_segment *newseg)
{
	t_segment	*cur;

	if (!head || !newseg)
		return ;
	if (*head == NULL)
	{
		*head = newseg;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = newseg;
}

static size_t	segs_len(t_segment *segments)
{
	t_segment	*current;
	char		*temp;
	size_t		len;

	current = segments;
	len = 0;
	while (current)
	{
		if (current->q_type == Q_SINGLE)
			len += ft_strlen(current->value);
		else
		{
			temp = expand_vars(current->value);
			len += ft_strlen(temp);
			free_collector_one(temp);
		}
		current = current->next;
	}
	return (len);
}

static void	copy_segs(t_segment *segments, char *buff)
{
	t_segment	*current;
	char		*temp;
	char		*p;

	current = segments;
	p = buff;
	while (current)
	{
		if (current->q_type == Q_SINGLE)
		{
			ft_memcpy(p, current->value, ft_strlen(current->value));
			p += ft_strlen(current->value);
		}
		else
		{
			temp = expand_vars(current->value);
			ft_memcpy(p, temp, ft_strlen(temp));
			p += ft_strlen(temp);
			free_collector_one(temp);
		}
		current = current->next;
	}
	*p = '\0';
}

char	*join_segs(t_segment *segments)
{
	size_t	len;
	char	*buff;

	len = segs_len(segments);
	buff = safe_malloc(len + 1);
	copy_segs(segments, buff);
	return (buff);
}

int	create_seg(t_tokens **tokens, t_segment *segments)
{
	t_tokens	*new_token;
	t_tokens	*cur;
	char		*joined;

	joined = join_segs(segments);
	if (!joined)
		return (-1);
	new_token = safe_malloc(sizeof(t_tokens));
	if (!new_token)
		return (free_collector_all(1), -1);
	new_token->value = joined;
	new_token->type = WORD;
	new_token->segments = segments;
	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		cur = *tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
	}
	return (1);
}
