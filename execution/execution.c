/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:16:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/21 20:13:29 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_child(int n_cmd, int **pipefd, int i_cmd, t_cmd *cmd)
{
	int	reds;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_pipes(n_cmd, pipefd, i_cmd);
	if (cmd->reds)
	{
		if (!cmd->args[0])
			reds = execute_redirections(cmd->reds, 0);
		else
			reds = execute_redirections(cmd->reds, 1);
		if (reds == 1 || !cmd->args[0])
		{
			free_collector_all(0);
			exit(reds);
		}
	}
}

pid_t	execute_one_command(t_cmd *cmd, int n_cmd, int **pipefd, int i_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_child(n_cmd, pipefd, i_cmd, cmd);
		if (cmd->args[0] && cmd->type == OUTSIDER)
			execute_outsider_cmd(cmd);
		else if (cmd->args[0] && cmd->type == BUILTINS)
			execute_builtins_cmd(cmd);
		free_collector_all(0);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (pid);
}

void	execution_init(void)
{
	t_cmd	*here;
	t_cmd	*tmp;
	int		flag;

	builting_exit();
	setup_types();
	here = g_structs.cmd;
	flag = 0;
	tmp = here;
	while (here)
	{
		if (here->reds && here->reds->type == R_HEREDOC)
		{
			tmp = here;
			flag = 1;
		}
		here = here->next;
	}
	if (!flag)
		return ;
	handle_heredocs(tmp->reds);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	execute_cmd_helper(void)
{
	pid_t	pid;
	int		wstatus;

	pid = execute_one_command(g_structs.cmd, 0, NULL, 0);
	waitpid(pid, &wstatus, 0);
	g_structs.exit_status = WEXITSTATUS(wstatus);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (WTERMSIG(wstatus) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_structs.exit_status = 130;
	}
	else if (WTERMSIG(wstatus) == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_structs.exit_status = 130;
	}
}

void	execution(void)
{
	int	num_cmd;

	if (!g_structs.cmd)
	{
		g_structs.exit_status = 2;
		return ;
	}
	execution_init();
	num_cmd = n_cmd(g_structs.cmd);
	if (num_cmd == 1)
	{
		if (g_structs.cmd->type == BUILTINS && !g_structs.cmd->reds)
			execute_builtins_cmd(g_structs.cmd);
		else
			execute_cmd_helper();
	}
	else if (num_cmd > 1)
		execute_multiple_command(num_cmd);
}
