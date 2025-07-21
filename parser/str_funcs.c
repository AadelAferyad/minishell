/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:01:42 by imellali          #+#    #+#             */
/*   Updated: 2025/07/18 01:33:56 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

char	*extracting_word(char *input, int start, int end)
{
	char	*word;

	word = ft_substr(input, start, end - start);
	if (!word)
	{
		free_collector_all(1);
		return (NULL);
	}
	return (word);
}

char	*safe_strjoin(char *s1, char *s2)
{
	if (s1)
		return (ft_strjoin(s1, s2));
	else
		return (ft_strdup(s2));
}

void	append_to_output(char **dst, char *src)
{
	char	*tmp;
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = 0;
	if (*dst)
		while ((*dst)[dest_len])
			dest_len++;
	src_len = 0;
	while (src && src[src_len])
		src_len++;
	tmp = safe_malloc(dest_len + src_len + 1);
	if (!tmp)
		return ;
	i = -1;
	while (++i < dest_len)
		tmp[i] = (*dst)[i];
	i = -1;
	while (++i < src_len)
		tmp[dest_len + i] = src[i];
	tmp[dest_len + src_len] = '\0';
	free_collector_one(*dst);
	*dst = tmp;
}
