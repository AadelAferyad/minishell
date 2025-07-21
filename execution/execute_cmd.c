/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:41:41 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/20 21:57:00 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_outsider_cmd(t_cmd *cmd)
{
	char	*path;
	char	**envp;
	int		exit_s;

	path = check_add_path(cmd->args[0]);
	if (path)
	{
		envp = create_env_arr();
		execve(path, cmd->args, envp);
		ft_putstr_fd("execve failed : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_structs.exit_status = 126;
	}
	exit_s = g_structs.exit_status;
	free_collector_all(0);
	exit(exit_s);
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
		builtin_unset(&cmd->args[1]);
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

void	connect_heredoc(void)
{
	t_reds	*red;
	int		tmp_file;

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
