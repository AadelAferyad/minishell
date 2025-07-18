/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:16:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/09 12:59:41 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	execute_pipes(int n_cmd, int **pipefd, int i_cmd)
{
	int	i;

	i = 0;
	if (i_cmd > 0)
	{
		dup2(pipefd[i_cmd - 1][0], STDIN_FILENO);
	}
	if (i_cmd < n_cmd - 1)
	{
		dup2(pipefd[i_cmd][1], STDOUT_FILENO);
	}
	while (i < n_cmd - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void	execute_outsider_cmd(t_cmd *cmd)
{
	char	*path;
	char	**envp;

	path = check_add_path(cmd->args[0]);
	/*printf("here %s \n", path);*/
	if (path)
	{
		envp = create_env_arr();
		execve(path, cmd->args, envp);
		ft_putstr_fd("execve failed : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free_collector_all(0);
		exit(126);
	}
	free_collector_all(0);
	exit(127);
}

void	execute_builtins_cmd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		builtin_echo(&cmd->args[1]);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		builtin_cd(&cmd->args[1]);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		builtin_env();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		builtin_export(&cmd->args[1]);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		builtin_unset(cmd->args[1]);
}

void	def_sig(int sigint)
{
	if (sigint == SIGINT)
		printf("test\n");
}

pid_t	execute_one_command(t_cmd *cmd, int n_cmd, int **pipefd, int i_cmd)
{
	pid_t	pid;
	struct sigaction sa;
	int	reds;

	pid = fork();
	if (pid == 0)
	{
		sa.sa_handler = def_sig;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
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
		if (cmd->args[0] && cmd->type == OUTSIDER)
			execute_outsider_cmd(cmd);
		else if (cmd->args[0] && cmd->type == BUILTINS)
			execute_builtins_cmd(cmd);
		free_collector_all(0);
		exit(0);
	}
	return (pid);
}

void	execute_multiple_command(int num_cmd)
{
	int	**pipefd;
	pid_t	*children;
	t_cmd	*cmd;
	int	i;
	int	wstatus;

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
		}
		i++;
	}
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

void	connect_heredoc()
{
	t_reds	*red;
	int	tmp_file;

	red = g_structs.cmd->reds;
	red = get_last_heredoc(red);
	if (!red)
		return ;
	tmp_file = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (tmp_file == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	write(tmp_file, red->heredoc_buff, ft_strlen(red->heredoc_buff));
	close(tmp_file);
	red->type = R_IN;
	red->flag = "/tmp/heredoc";
}
void	builting_exit()
{
	char	*str;
	int		status;
;
	str = g_structs.cmd->args[1];
	status = 0;
	if (!ft_strncmp(g_structs.cmd->args[0], "exit", 4))
	{
		if (str && g_structs.cmd->args[2])
		{
				ft_putstr_fd("exit: too many arguments\n", 2);
				free_collector_all(0);
				exit(1);
		}
		if (str)
		{
			while (g_structs.cmd->args[1][status])
			{
				if (!ft_isdigit(str[status]) && (str[status] != '+' && str[status] != '-'))
				{
					ft_putstr_fd("exit: numeric argument required\n", 2);
					free_collector_all(0);
					exit(2);
				}
				status++;
			}
			status = ft_atoi(g_structs.cmd->args[1]);
		}
		else
			status = g_structs.exit_status;
		free_collector_all(0);
		exit(status);
	}
}
void	execution()
{
	int	num_cmd;
	int	wstatus;
	pid_t	pid;

	if (!g_structs.cmd)
	{
		g_structs.exit_status = 2;
		return ;
	}
	builting_exit();
	/*while (g_structs.cmd && !g_structs.cmd->args[0])*/
	/*{*/
	/*	execute_redirections(g_structs.cmd->reds, 0);*/
	/*	g_structs.cmd = g_structs.cmd->next;*/
	/*}*/
	handle_heredocs(g_structs.cmd->reds);
	setup_types();
	connect_heredoc();
	num_cmd = n_cmd(g_structs.cmd);
	if (num_cmd == 1)
	{
		if (g_structs.cmd->type == BUILTINS && !g_structs.cmd->reds)
		{
			execute_builtins_cmd(g_structs.cmd);
		}
		else
		{
			pid = execute_one_command(g_structs.cmd, 0, NULL, 0);
			waitpid(pid, &wstatus, 0);
			g_structs.exit_status = WEXITSTATUS(wstatus);
		}
	}
	else if (num_cmd > 1)
		execute_multiple_command(num_cmd);
}
