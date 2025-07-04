/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:34:03 by imellali          #+#    #+#             */
/*   Updated: 2025/07/04 16:10:26 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	trim(char *s)
{
	int		i;
	t_env	*node;
	t_env	*tmp;

	i = 0;
	tmp = g_structs.env;
	while (s[i] != '=')
		i++;
	node = safe_malloc(sizeof(t_env));
	node->key = ft_substr(s, 0, i);
	node->value = ft_substr(s, i + 1, ft_strlen(&s[i]));
	node->next = NULL;
	if (!tmp)
	{
		g_structs.env = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	create_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		trim(env[i]);
		i++;
	}
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

static void	append_to_output(char **dst, char *src)
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

static size_t	key_end(char *input, size_t i)
{
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (i);
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

static size_t	handle_env_var(char *input, size_t i, char **output)
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

void	add_char(char **dst, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	append_to_output(dst, buf);
}

char	*expand_vars(char *input)
{
	char	*output;
	size_t	i;

	output = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (!input[i])
				add_char(&output, '$');
			else if (ft_isalpha(input[i]) || input[i] == '_')
				i = handle_env_var(input, i, &output);
			else if (ft_isdigit(input[i]))
			{
				i++;
				while (ft_isdigit(input[i]))
				{
					add_char(&output, input[i]);
					i++;
				}
			}
			else
			{
				add_char(&output, '$');
				add_char(&output, input[i++]);
			}
		}
		else
			add_char(&output, input[i++]);
	}
	if (!output)
	{
		output = safe_malloc(1);
		output[0] = '\0';
	}
	return (output);
}
