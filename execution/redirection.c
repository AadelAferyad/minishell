/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:30:17 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/21 20:46:12 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirections_out(char *file, int flag)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_structs.exit_status = 1;
		return (1);
	}
	if (!flag)
	{
		close(fd);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirections_append(char *file, int flag)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_structs.exit_status = 1;
		return (1);
	}
	if (!flag)
	{
		close(fd);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirections_in(char *file, int flag)
{
	int	fd;

	if (access(file, F_OK) != 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_structs.exit_status = 1;
		return (1);
	}
	fd = open(file, O_RDONLY);
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
		{
			if (redirections_out(redirections->flag, just_create))
				return (1);
		}
		else if (redirections->type == R_APPEND)
		{
			if (redirections_append(redirections->flag, just_create))
				return (1);
		}
		else if (redirections->type == R_IN)
		{
			if (redirections_in(redirections->flag, just_create))
				return (1);
		}
		redirections = redirections->next;
	}
	return (0);
}
