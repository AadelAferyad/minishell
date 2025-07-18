/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:47:28 by imellali          #+#    #+#             */
/*   Updated: 2025/07/18 01:30:06 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	append_line(char **buff, const char *line)
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

static int	heredoc_loop(t_reds *redir, char **heredoc_buff, int is_quoted)
{
	char	*line;
	int		status;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_end(line, redir))
		{
			free_collector_one(line);
			break ;
		}
		status = store_line(heredoc_buff, line, is_quoted);
		free_collector_one(line);
		if (status == -1)
			return (-1);
	}
	return (0);
}

int	read_heredoc(t_reds *redir)
{
	char	*heredoc_buff;
	int		is_quoted;
	int		status;

	heredoc_buff = NULL;
	is_quoted = 0;
	if (redir->quoted)
		is_quoted = 1;
	status = heredoc_loop(redir, &heredoc_buff, is_quoted);
	set_buff(redir, heredoc_buff);
	return (status);
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
