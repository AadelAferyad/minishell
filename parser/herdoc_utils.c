/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:24:45 by imellali          #+#    #+#             */
/*   Updated: 2025/07/18 01:26:10 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_end(char *line, t_reds *redir)
{
	if (ft_strcmp(line, redir->flag) == 1)
		return (1);
	return (0);
}

int	store_line(char **heredoc_buff, char *line, int is_quoted)
{
	char	*to_store;

	to_store = NULL;
	if (!is_quoted)
		to_store = expand_vars(line);
	else
		to_store = ft_strdup(line);
	if (!to_store)
	{
		free_collector_one(line);
		free_collector_one(*heredoc_buff);
		return (-1);
	}
	append_line(heredoc_buff, to_store);
	free_collector_one(to_store);
	if (!*heredoc_buff)
		return (-1);
	return (0);
}

void	set_buff(t_reds *redir, char *heredoc_buff)
{
	if (heredoc_buff)
		redir->heredoc_buff = heredoc_buff;
	else
		redir->heredoc_buff = ft_strdup("");
}
