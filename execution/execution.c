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
		if (!access(full_path, X_OK))
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

char	*check_add_path(char *single_cmd)
{
	char	**path;
	char	*extracted_path;
	char	*full_path;

	if (!access(single_cmd, X_OK))
		return (single_cmd);
	extracted_path = extract_path();
	if (!extracted_path)
		return (NULL);
	path = ft_split(extracted_path, ':');
	full_path = find_right_path(single_cmd, path);
	free_list_of_path(path);
	return (full_path);
}

void	execution()
{
	t_cmd	*cmd;
	char	*single_cmd;
	char	*full_path;
	char	**envp;
	pid_t	pid;
	int	wstatus;

	cmd = g_structs.cmd;
	envp = create_env_arr();
	while (cmd)
	{
		single_cmd = cmd->args[0];
		full_path = check_add_path(single_cmd);
		if (!full_path)
		{
			if (!access(single_cmd, F_OK))
				ft_putstr_fd("dasdas\n", 1);
			full_path = single_cmd;
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			execve(full_path, cmd->args, envp);
			ft_putstr_fd(strerror(errno), 2);
			exit(12);
		}
		waitpid(pid, &wstatus, 0);
		if (wstatus == 12)
			ft_putstr_fd("works", 1);
		cmd = cmd->next;
	}
}
