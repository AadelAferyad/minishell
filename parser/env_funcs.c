/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 02:10:16 by imellali          #+#    #+#             */
/*   Updated: 2025/07/05 23:15:02 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	strjoin_with_space(char **dst, const char *src)
{
	char	*tmp;
	size_t	len_dst;
	size_t	len_src;

	len_dst = *dst ? strlen(*dst) : 0;
	len_src = strlen(src);
	tmp = safe_malloc(len_dst + len_src + 2);
	if (len_dst)
	{
		strcpy(tmp, *dst);
		tmp[len_dst] = ' ';
		strcpy(tmp + len_dst + 1, src);
	}
	else
	{
		strcpy(tmp, src);
	}
	free_collector_one(*dst);
	*dst = tmp;
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

static int	count_fields(const char *str)
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

char	**field_splitting(const char *value)
{
	int		i;
	int		start;
	int		word_idx;
	int		num_fields;
	char	**fields;

	i = 0;
	word_idx = 0;
	if (!value)
		return (NULL);
	num_fields = count_fields(value);
	fields = safe_malloc(sizeof(char *) * (num_fields + 1));
	if (!fields)
		return (NULL);
	while (value[i])
	{
		while (value[i] && ft_isspace(value[i]))
			i++;
		if (!value[i])
			break ;
		start = i;
		while (value[i] && !ft_isspace(value[i]))
			i++;
		fields[word_idx++] = ft_substr(value, start, i - start);
	}
	fields[word_idx] = NULL;
	return (fields);
}

char	*get_env_value(char *varname)
{
	t_env	*env;

	env = g_structs.env;
	while (env)
	{
		if (ft_strcmp(env->key, varname) == 1)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*key_varname(char *input, size_t start, size_t end)
{
	char	*var;
	size_t	j;

	var = safe_malloc(end - start + 1);
	if (!var)
		return (NULL);
	j = 0;
	while (start < end)
		var[j++] = input[start++];
	var[j] = '\0';
	return (var);
}

size_t	handle_env_var(char *input, size_t i, char **output)
{
	size_t	end;
	char	*key;
	char	*value;

	end = key_end(input, i);
	key = key_varname(input, i, end);
	value = get_env_value(key);
	if (!value)
		value = "";
	append_to_output(output, value);
	free_collector_one(key);
	return (end);
}
