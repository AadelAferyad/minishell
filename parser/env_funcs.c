/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 02:10:16 by imellali          #+#    #+#             */
/*   Updated: 2025/07/09 12:35:59 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>

char	*get_env_value(char *varname)
{
	t_env	*env;

	env = *get_env();
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
