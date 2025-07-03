/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:05:56 by imellali          #+#    #+#             */
/*   Updated: 2025/07/03 15:07:42 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static char	*join_seg(t_segment *segments)
{
	t_segment	*current;
	size_t		len;
	size_t		slen;
	char		*res;
	char		*p;

	len = 0;
	current = segments;
	while (current)
	{
		len += ft_strlen(current->value);
		current = current->next;
	}
	res = safe_malloc(len + 1);
	p = res;
	current = segments;
	while (current)
	{
		slen = ft_strlen(current->value);
		ft_memcpy(p, current->value, slen);
		p += slen;
		current = current->next;
	}
	*p = '\0';
	return (res);
}

int	create_seg(t_tokens **tokens, t_segment *segments)
{
	t_tokens	*new_token;
	t_tokens	*cur;
	char		*joined;

	joined = join_seg(segments);
	if (!joined)
		return (-1);
	new_token = safe_malloc(sizeof(t_tokens));
	if (!new_token)
		return (free_collector_all(), -1);
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
