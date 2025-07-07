/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:34:03 by imellali          #+#    #+#             */
/*   Updated: 2025/07/05 17:10:35 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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

size_t	key_end(char *input, size_t i)
{
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (i);
}

void	add_char(char **dst, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	append_to_output(dst, buf);
}

static size_t	expand(char *input, size_t i, char **output)
{
	if (!input[i])
		add_char(output, '$');
	else if (ft_isalpha(input[i]) || input[i] == '_')
		i = handle_env_var(input, i, output);
	else if (ft_isdigit(input[i]))
	{
		i++;
		while (ft_isdigit(input[i]))
		{
			add_char(output, input[i]);
			i++;
		}
	}
	else
	{
		add_char(output, '$');
		add_char(output, input[i++]);
	}
	return (i);
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
			i = expand(input, i, &output);
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
