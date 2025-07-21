/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:47:28 by imellali          #+#    #+#             */
/*   Updated: 2025/07/21 21:21:42 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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

void	here_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		if (access("/tmp/heredoc", F_OK))
			unlink("/tmp/heredoc");
		free_collector_all(0);
		exit(130);
	}
	else if (sig == EOF)
	{
		ft_putstr_fd("\n", 1);
		if (access("/tmp/heredoc", F_OK))
			unlink("/tmp/heredoc");
		free_collector_all(0);
		exit(130);
	}
}

void	parent_state(t_reds *current, pid_t pid)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	current = get_last_heredoc(current);
	if (WEXITSTATUS(status) == 130)
	{
		g_structs.cmd = NULL;
		g_structs.exit_status = 130;
	}
	else if (WEXITSTATUS(status) == 2)
	{
		g_structs.exit_status = 0;
		current->type = R_IN;
		current->flag = "/tmp/heredoc";
	}
	else if (current)
	{
		current->type = R_IN;
		current->flag = "/tmp/heredoc";
	}
}

void	here_doc_child(t_reds *current)
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

int	handle_heredocs(t_reds *reds)
{
	t_reds	*current;
	pid_t	pid;

	pid = fork();
	signal(SIGINT, here_sig);
	current = reds;
	if (pid == 0)
		here_doc_child(current);
	else
		parent_state(current, pid);
	return (0);
}
