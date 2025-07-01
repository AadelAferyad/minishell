/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:16:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/27 14:39:51 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <execution.h>

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
		{
			ft_putstr_fd("found path: ", 1);
			ft_putstr_fd(full_path, 1);
			ft_putstr_fd("\n", 1);
			return (full_path);
		}
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
	}
	return (full_path);
}

char	*check_add_path(char *single_cmd)
{
	struct stat	st;

	stat(single_cmd, &st);
	if (access(single_cmd, X_OK) == 0 && !S_ISDIR(st.st_mode))
	{
		if (!(single_cmd[0] == '.' && single_cmd[1] == '/'))
			return (NULL);
		return (single_cmd);
	}
	if (S_ISDIR(st.st_mode) && ft_strchr(single_cmd, '/'))
	{
		ft_putstr_fd(single_cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (NULL);
	}
	if (ft_strchr(single_cmd, '/'))
	{
		ft_putstr_fd(single_cmd, 2);
		ft_putstr_fd(": No such a file or directory\n", 2);
		return (NULL);
	}
	return (generate_right_path(single_cmd));
}

void	execute(char *full_path, char **args, int *pipefd)
{
	pid_t	pid;
	int	wstatus;
	char	**envp;

	pid = fork();
	if (pid < 0)
		exit(1);
	envp = create_env_arr();
	if (pid == 0)
	{
		execve(full_path, args, envp);
		if (pipefd)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		ft_putstr_fd(strerror(errno), 2);
		exit(12);
	}
	else
		waitpid(pid, &wstatus, 0);
}

void	redirections_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	redirections_in(char *file)
{
	int	fd;

	if (access(file, F_OK) != 0)
	{
		ft_putstr_fd(": No such a file or directory\n", 2);
		return (1);
	}
	fd = open(file, O_APPEND);
	if (fd == -1)
		// error !
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	execute_redirections(t_reds *redirections)
{
	while (redirections)
	{
		if (redirections->type == R_OUT)
			redirections_out(redirections->flag);
		else if (redirections->type == R_IN)
		{
			if (redirections_in(redirections->flag))
				return (1);
		}
		redirections = redirections->next;
	}
	return (0);
}

void	execution()
{
	t_cmd	*cmd;
	char	*single_cmd;
	char	*full_path;
	int	std_out;
	int	std_in;
	int	pipefd[2];
	int	*is_pipe;


	cmd = g_structs.cmd;
	//saved stdout
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	is_pipe = NULL;
	while (cmd)
	{
		ft_putstr_fd(cmd->args[0], 1);
		if (cmd->next)
		{
			ft_putstr_fd("\ninside pipe\n", 1);
			pipe(pipefd);
			dup2(pipefd[0], STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			is_pipe = pipefd;

		}
		if (cmd->reds)
			execute_redirections(cmd->reds);
		single_cmd = cmd->args[0];
		full_path = check_add_path(single_cmd);
		if (full_path)
			execute(full_path, cmd->args, is_pipe);
		if (is_pipe)
		{
			is_pipe = NULL;
		}
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			dup2(std_out, STDOUT_FILENO);
			dup2(std_in, STDIN_FILENO);
		}
		cmd = cmd->next;
	}
	close(std_out);
	close(std_in);
}
