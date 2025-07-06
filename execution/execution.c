/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:16:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/05 16:28:11 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

char	*extract_path()
{
	char	*path;
	t_env	*envp;

	path = NULL;
	envp = g_structs.env;
	if (!envp)
		return (NULL);
	while (envp)
	{
		if (ft_strncmp(envp->key, "PATH", 4) == 0)
		{
			path = ft_strdup(envp->value);
			break ;
		}
		envp = envp->next;
	}
	return (path);
}

char	*find_right_path(char *single_cmd, char **path)
{
	int	i;
	char	*sub_path;
	char	*full_path;

	i = 0;
	while (path[i])
	{
		sub_path = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(sub_path, single_cmd);
		free_collector_one(sub_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free_collector_one(full_path);
		i++;
	}
	return (NULL);
}

static void	free_list_of_path(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free_collector_one(grid[i]);
		grid[i] = NULL;
		i++;
	}
	free_collector_one(grid);
	grid = NULL;
}

char	*check_is_valid_cmd(char *single_cmd)
{
	if (single_cmd[0] == '/')
		return (NULL);
	return (NULL);
}

char	*generate_right_path(char *single_cmd)
{
	char	**path;
	char	*extracted_path;
	char	*full_path;

	extracted_path = extract_path();
	if (!extracted_path)
		return (NULL);
	path = ft_split(extracted_path, ':');
	full_path = find_right_path(single_cmd, path);
	free_list_of_path(path);
	if (!full_path)
	{
		ft_putstr_fd(single_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_structs.exit_status = 127;
	}
	return (full_path);
}

char	*file_exists(char *single_cmd)
{
	struct stat	st;

	stat(single_cmd, &st);
	if (access(single_cmd, X_OK) == 0 && !S_ISDIR(st.st_mode))
	{
		if (single_cmd[0] == '.') 
		{
			if (single_cmd[1] != '/')
				return (NULL);
		}
		return (single_cmd);
	}
	if (S_ISDIR(st.st_mode) && ft_strchr(single_cmd, '/'))
	{
		ft_putstr_fd(single_cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_structs.exit_status = 126;
		return (NULL);
	}
	return (generate_right_path(single_cmd));
}

char	*check_add_path(char *single_cmd)
{
	if (access(single_cmd, F_OK) == 0)
	{
		return (file_exists(single_cmd));
	}
	else if (ft_strchr(single_cmd, '/'))
	{
		ft_putstr_fd(single_cmd, 2);
		ft_putstr_fd(": No such a file or directory\n", 2);
		g_structs.exit_status = 127;
		return (NULL);
	}
	return (generate_right_path(single_cmd));
}

void	redirections_out(char *file, int flag)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	if (!flag)
	{
		close(fd);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirections_append(char *file, int flag)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	if (!flag)
	{
		close(fd);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
int	redirections_in(char *file, int flag)
{
	int	fd;

	if (access(file, F_OK) != 0)
	{

		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such a file or directory\n", 2);
		g_structs.exit_status = 1;
		return (1);
	}
	fd = open(file, O_APPEND);
	if (fd == -1)
	{
		ft_putstr_fd("Could not open a fail\n", 2);
		free_collector_all(0);
		exit(1);
	}
	if (!flag)
	{
		close(fd);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	execute_redirections(t_reds *redirections, int just_create)
{
	while (redirections)
	{
		if (redirections->type == R_OUT)
			redirections_out(redirections->flag, just_create);
		if (redirections->type == R_APPEND)
			redirections_append(redirections->flag, just_create);
		else if (redirections->type == R_IN)
		{
			if (redirections_in(redirections->flag, just_create))
				return (1);
		}
		redirections = redirections->next;
	}
	return (0);
}

int	n_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

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

char	**builtins_array()
{
	char	**arr;

	arr = safe_malloc(sizeof(char *) * 8)
	arr[0] = ft_strdup("echo");
	arr[1] = ft_strdup("cd");
	arr[2] = ft_strdup("pwd");
	arr[3] = ft_strdup("export");
	arr[4] = ft_strdup("unset");
	arr[5] = ft_strdup("env");
	arr[6] = ft_strdup("exit");
	arr[7] = NULL;
	return (arr);
}

void	free_builtins_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free_collector_one(arr[i]);
		i++;
	}
	arr = NULL;
}

void	execute_outsider_cmd(t_cmd *cmd, char **envp)
{
	char	*path;

	path = check_add_path(cmd->args[0]);
	if (path)
	{
		execve(path, cmd->args, envp);
		ft_putstr_fd("execve failed : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_structs.exit_status = 126;
		free_collector_all(0);
		exit(0);
	}
	else
	{
		free_collector_all(0);
		exit(0);
	}
}

void	execute_builtins_cmd(t_cmd *cmd)
{
	char	**arr;
	int	i;

	i = 0;
	arr = builtins_array();
	if ()
	free_builtins_arr(arr);
}

pid_t	execute_one_command(t_cmd *cmd, int n_cmd, int **pipefd, int i_cmd)
{
	pid_t	pid;
	char	**envp;
	char	*path;

	pid = fork();
	envp = create_env_arr();
	path = NULL;
	if (pid == 0)
	{
		execute_pipes(n_cmd, pipefd, i_cmd);
		if (cmd->reds)
			execute_redirections(cmd->reds, 1);
		if (cmd->args[0] && cmd->type == OUTSIDER)
			execute_outsider_cmd(cmd, envp);
		else if (cmd->args[0] && cmd->type == BUILTINS)
			execute_builtins_cmd(cmd);

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
	pipefd = safe_malloc(sizeof(int *) * (num_cmd - 1));
	children = safe_malloc(sizeof(pid_t) * num_cmd);
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
		waitpid(children[i], &wstatus, 0);
		i++;
	}
}

void	setup_helper(char **arr, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (arr[i])
		{
			if (ft_strncmp(cmd->args[0], arr[i], ft_strlen(arr[i])) == 0)
			{
				cmd->type = BUILTINS;
				i = 0;
				break ; 
			}
			i++;
		}
		if (i)
			cmd->type = OUTSIDER;
		cmd = cmd->next;
	}
}


void	setup_types()
{
	char	**arr;
	int	i;

	i = 0;
	arr = builtins_array();
	setup_helper(arr, g_structs.cmd);
	free_builtins_arr(arr);
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
	while (!g_structs.cmd->args[0])
	{
		execute_redirections(g_structs.cmd->reds, 0);
		g_structs.cmd = g_structs.cmd->next;
	}
	setup_types();
	num_cmd = n_cmd(g_structs.cmd);
	if (num_cmd == 1)
	{
		pid = execute_one_command(g_structs.cmd, 0, NULL, 0);
		waitpid(pid, &wstatus, 0);
		g_structs.exit_status = wstatus;
	}
	else
		execute_multiple_command(num_cmd);
}
