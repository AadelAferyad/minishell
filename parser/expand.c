/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:34:03 by imellali          #+#    #+#             */
/*   Updated: 2025/07/18 01:33:58 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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

static void	handle_exit_status(char **output)
{
	char	*exit_status;

	exit_status = ft_itoa(g_structs.exit_status);
	append_to_output(output, exit_status);
	free_collector_one(exit_status);
}

static size_t	expand(char *input, size_t i, char **output)
{
	if (!input[i])
		add_char(output, '$');
	else if (input[i] == '?')
	{
		handle_exit_status(output);
		i++;
	}
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
		add_char(output, input[i]);
		i++;
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
