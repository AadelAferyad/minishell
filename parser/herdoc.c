/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:15:18 by imellali          #+#    #+#             */
/*   Updated: 2025/07/15 12:45:36 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	validate_redir_syntax(t_tokens **cur, t_cmd *cmd)
{
	if (!(*cur)->next || !is_word((*cur)->next->type))
	{
		if ((*cur)->next)
			syntax_error((*cur)->next->value);
		else
			syntax_error("newline");
		free_collector_one(cmd);
		return (-1);
	}
	return (0);
}

static int	is_seg_quoted(t_segment *segments)
{
	t_segment	*seg;

	seg = segments;
	while (seg)
	{
		if (seg->q_type != Q_NONE)
			return (1);
		seg = seg->next;
	}
	return (0);
}

static char	*concat_segs(t_segment *segments)
{
	size_t		len;
	t_segment	*seg;
	char		*res;

	len = 0;
	seg = segments;
	while (seg)
	{
		len += ft_strlen(seg->value);
		seg = seg->next;
	}
	res = safe_malloc(len + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	seg = segments;
	while (seg)
	{
		ft_strlcat(res, seg->value, len + 1);
		seg = seg->next;
	}
	return (res);
}

int	process_heredoc_redir(t_tokens *delim_token, t_reds **reds, t_cmd *cmd)
{
	int		quoted;
	char	*delimiter;

	if (!delim_token || !delim_token->segments)
		return (-1);
	quoted = is_seg_quoted(delim_token->segments);
	delimiter = concat_segs(delim_token->segments);
	if (!delimiter)
		return (-1);
	*reds = add_redir(*reds, R_HEREDOC, delimiter, quoted);
	free_collector_one(delimiter);
	if (!*reds)
	{
		free_collector_one(cmd);
		return (-1);
	}
	return (0);
}
