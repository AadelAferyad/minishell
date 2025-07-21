/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:41:20 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/21 20:34:15 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	if (single_cmd[0] == '.' && single_cmd[1] == '/')
		return (single_cmd);
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
		ft_putstr_fd(": No such file or directory\n", 2);
		g_structs.exit_status = 127;
		return (NULL);
	}
	return (generate_right_path(single_cmd));
}

int	n_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static void	setup_helper(char **arr, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (arr[i])
		{
			if (cmd->args[0]
				&& ft_strncmp(cmd->args[0], arr[i], ft_strlen(arr[i])) == 0)
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

void	setup_types(void)
{
	char	*arr[8];
	int		i;

	arr[0] = ft_strdup("echo");
	arr[1] = ft_strdup("cd");
	arr[2] = ft_strdup("pwd");
	arr[3] = ft_strdup("export");
	arr[4] = ft_strdup("unset");
	arr[5] = ft_strdup("env");
	arr[6] = ft_strdup("exit");
	arr[7] = NULL;
	i = 0;
	setup_helper(arr, g_structs.cmd);
	while (arr[i])
	{
		free_collector_one(arr[i]);
		i++;
	}
}
