/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:47:28 by imellali          #+#    #+#             */
/*   Updated: 2025/07/15 12:47:32 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	append_line(char **buff, const char *line)
{
	size_t	old_len;
	size_t	line_len;
	char	*new_buff;

	if (*buff)
		old_len = ft_strlen(*buff);
	else
		old_len = 0;
	line_len = ft_strlen(line);
	new_buff = safe_malloc(old_len + line_len + 2);
	if (!new_buff)
	{
		free_collector_one(*buff);
		*buff = NULL;
		return ;
	}
	if (*buff)
		ft_memcpy(new_buff, *buff, old_len);
	ft_memcpy(new_buff + old_len, line, line_len);
	new_buff[old_len + line_len] = '\n';
	new_buff[old_len + line_len + 1] = '\0';
	free_collector_one(*buff);
	*buff = new_buff;
}

static int	read_heredoc(t_reds *redir)
{
	char	*heredoc_buff;
	char	*line;
	int		is_quoted;
	char	*to_store;

	heredoc_buff = NULL;
	line = NULL;
	is_quoted = 0;
	if (redir->quoted)
		is_quoted = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->flag) == 1)
		{
			free_collector_one(line);
			break ;
		}
		to_store = NULL;
		if (!is_quoted)
			to_store = expand_vars(line);
		else
			to_store = ft_strdup(line);
		if (!to_store)
			return (free_collector_one(line), free_collector_one(heredoc_buff),
				-1);
		append_line(&heredoc_buff, to_store);
		free_collector_one(line);
		free_collector_one(to_store);
		if (!heredoc_buff)
			return (-1);
	}
	if (heredoc_buff)
		redir->heredoc_buff = heredoc_buff;
	else
		redir->heredoc_buff = ft_strdup("");
	return (0);
}

int	handle_heredocs(t_reds *reds)
{
	t_reds	*current;

	current = reds;
	while (current)
	{
		if (current->type == R_HEREDOC)
		{
			if (read_heredoc(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
