/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:01:42 by imellali          #+#    #+#             */
/*   Updated: 2025/06/25 16:19:25 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

	word = safe_substr(input, start, end - start);
	if (!word)
	{
		free_collector_all();
		return (NULL);
	}
	return (word);
}

char	*safe_strdup(char *s)
{
	char	*word;

	word = ft_strdup(s);
	if (!word)
		return (NULL);
	add_node(word);
	return (word);
}

char	*safe_substr(char *s, unsigned int start, size_t len)
{
	char	*word;

	word = ft_substr(s, start, len);
	if (!word)
		return (NULL);
	add_node(word);
	return (word);
}
