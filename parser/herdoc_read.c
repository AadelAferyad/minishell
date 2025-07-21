/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:47:28 by imellali          #+#    #+#             */
/*   Updated: 2025/07/21 19:13:49 by aaferyad         ###   ########.fr       */
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

t_reds	*get_last_heredoc(t_reds *reds)
{
	t_reds	*last;

	last = NULL;
	if (!reds)
		return (NULL);
	while (reds)
	{
		if (reds->type == R_HEREDOC)
			last = reds;
		reds = reds->next;
	}
	return (last);
}

void	connect_heredoc(char **heredoc_buff)
{
	int		tmp_file;

	tmp_file = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (tmp_file == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	if (heredoc_buff &&heredoc_buff[0])
		write(tmp_file, *heredoc_buff, ft_strlen(*heredoc_buff));
	close(tmp_file);
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
			free(line);
			connect_heredoc(heredoc_buff);
			break ;
		}
		status = store_line(heredoc_buff, line, is_quoted);
		free(line);
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
	int	status;
	pid_t	pid;

	pid = fork();
	signal(SIGINT, SIG_DFL);
	current = reds;
	if (pid == 0)
	{
		while (current)
		{
			if (current->type == R_HEREDOC)
			{
				if (read_heredoc(current) == -1)
				{
					free_collector_all(0);
					exit(0);
				}
			}
			current = current->next;
		}
		free_collector_all(0);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		current = get_last_heredoc(current);
		if (current)
		{
			current->type = R_IN;
			current->flag = "/tmp/heredoc";
		}
	}
	return (0);
}
