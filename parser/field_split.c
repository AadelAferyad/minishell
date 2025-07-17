/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:48:49 by imellali          #+#    #+#             */
/*   Updated: 2025/07/09 12:07:25 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	free_fields(char **fields)
{
	int	i;

	if (!fields)
		return ;
	i = 0;
	while (fields[i])
	{
		free_collector_one(fields[i]);
		i++;
	}
	free_collector_one(fields);
}

char	*join_words(char *joined, char *word)
{
	char	*temp;
	size_t	dest_len;
	size_t	src_len;

	if (*joined)
		dest_len = ft_strlen(joined);
	else
		dest_len = 0;
	src_len = ft_strlen(word);
	temp = safe_malloc(dest_len + src_len + 2);
	if (dest_len)
	{
		ft_strlcpy(temp, joined, dest_len + 1);
		temp[dest_len] = ' ';
		ft_strlcpy(temp + dest_len + 1, joined, src_len + 1);
	}
	else
		ft_strlcpy(temp, joined, src_len);
	free_collector_one(joined);
	return (temp);
}

static int	count_fields(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

static int	extract_field( char **fields, int *i, char *value, int idx)
{
	int	start;

	while (value[*i] && ft_isspace(value[*i]))
		(*i)++;
	if (!value[*i])
		return (0);
	start = *i;
	while (value[*i] && !ft_isspace(value[*i]))
		(*i)++;
	fields[idx] = ft_substr(value, start, *i - start);
	return (1);
}

char	**field_splitting(char *value)
{
	int		i;
	int		idx;
	int		num_fields;
	char	**fields;

	i = 0;
	idx = 0;
	if (!value)
		return (NULL);
	num_fields = count_fields(value);
	fields = safe_malloc(sizeof(char *) * (num_fields + 1));
	if (!fields)
		return (NULL);
	while (value[i])
	{
		if (!extract_field(fields, &i, value, idx))
			break ;
		idx++;
	}
	fields[idx] = NULL;
	return (fields);
}
