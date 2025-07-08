/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:17:44 by imellali          #+#    #+#             */
/*   Updated: 2025/07/08 17:14:03 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_global	g_structs;

void	print_segments(t_segment *segments)
{
	int	i;

	i = 0;
	while (segments)
	{
		printf("    [segment]: value=%s, quote_type=%d\n\n",
				segments->value,
				segments->q_type);
		segments = segments->next;
		i++;
	}
}

static void	print_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("VALUE =  [%s]   TYPE = %u\n", tokens->value, tokens->type);
		print_segments(tokens->segments);
		tokens = tokens->next;
		i++;
	}
}

static void	print_reds(t_reds *reds)
{
	while (reds)
	{
		printf("    [redir] type: %d, flag: %s, flag_quoted: %d\n", reds->type,
				reds->flag, reds->quoted);
		reds = reds->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds)
	{
		printf("Command #%d:\n", i++);
		if (cmds->args)
		{
			j = 0;
			while (cmds->args[j])
			{
				printf("  [arg %d]: %s\n", j, cmds->args[j]);
				j++;
			}
		}
		else
			printf("  [no args]\n");
		if (cmds->reds)
			print_reds(cmds->reds);
		else
			printf("  [no redirections]\n");
		cmds = cmds->next;
		printf("\n");
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

t_reds	*get_last_heredoc(t_reds *reds)
{
	t_reds	*last;

	last = NULL;
	while (reds)
	{
		if (reds->type == R_HEREDOC)
			last = reds;
		reds = reds->next;
	}
	return (last);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_tokens	*tokens;
	t_cmd		*cmds;
	t_reds		*heredoc;

	(void)argc;
	(void)argv;
	g_structs.env = NULL;
	// print_env(g_structs.env);
	create_env(envp);
	input = readline("marvel$> ");
	if (!input)
		return (free_collector_all(1), -1);
	tokens = lexer(input);
	if (!tokens)
		return (free_collector_all(1), -1);
	print_tokens(tokens);
	cmds = parse_tokens(tokens);
	if (!cmds)
		return (free_collector_all(1), -1);
	print_cmds(cmds);
	handle_all_heredocs(cmds->reds);
	heredoc = get_last_heredoc(cmds->reds);
	if (heredoc)
		printf("%s", heredoc->heredoc_buff);
	free_collector_all(1);
	return (0);
}
