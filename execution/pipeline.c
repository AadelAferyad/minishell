/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:08:39 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/21 12:11:41 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
