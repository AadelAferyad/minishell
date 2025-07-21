/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:49:25 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/21 20:53:06 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	closing_pipes_and_wait(int num_cmd, int **pipefd, pid_t *children)
{
	int	wstatus;
	int	i;

	i = 0;
	while (i < num_cmd - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < num_cmd)
	{
		if (children[i] > 0)
		{
			waitpid(children[i], &wstatus, 0);
			g_structs.exit_status = WEXITSTATUS(wstatus);
			if (WTERMSIG(wstatus) == SIGINT)
			{
				write(1, "\n", 1);
				g_structs.exit_status = 130;
			}
		}
		i++;
	}
}

void	execute_multiple_command(int num_cmd)
{
	int		**pipefd;
	pid_t	*children;
	t_cmd	*cmd;
	int		i;

	cmd = g_structs.cmd;
	pipefd = safe_malloc(sizeof(int *) * (num_cmd));
	children = safe_malloc(sizeof(pid_t) * (num_cmd + 1));
	i = 0;
	while (i < num_cmd - 1)
	{
		pipefd[i] = safe_malloc(sizeof(int) * 2);
		pipe(pipefd[i]);
		i++;
	}
	i = 0;
	while (i < num_cmd && cmd)
	{
		children[i] = execute_one_command(cmd, num_cmd, pipefd, i);
		cmd = cmd->next;
		i++;
	}
	closing_pipes_and_wait(num_cmd, pipefd, children);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static int	checking_exit_args(char *s)
{
	int		i;
	int		flag;
	long	n;

	i = 0;
	flag = 0;
	n = ft_atoi(g_structs.cmd->args[1]);
	while (g_structs.cmd->args[1][i])
	{
		if (!ft_isdigit(s[i]))
		{
			if (!flag && (s[i] == '+' || s[i] == '-'))
				flag++;
			else
			{
				ft_putstr_fd("exit\nexit: numeric argument required\n", 2);
				free_collector_all(0);
				exit(2);
			}
		}
		i++;
	}
	return (n);
}

void	builting_exit(void)
{
	char	*str;
	int		status;

	if (!g_structs.cmd->args || !g_structs.cmd->args[0])
		return ;
	str = g_structs.cmd->args[1];
	status = 0;
	if (!ft_strncmp(g_structs.cmd->args[0], "exit", 4))
	{
		if (str && g_structs.cmd->args[2])
		{
			ft_putstr_fd("exit\nexit: too many arguments\n", 2);
			free_collector_all(0);
			exit(1);
		}
		if (str)
			status = checking_exit_args(str);
		else
			status = g_structs.exit_status;
		free_collector_all(0);
		ft_putstr_fd("exit\n", 1);
		exit(status);
	}
}
