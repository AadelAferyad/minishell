/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:01:37 by imellali          #+#    #+#             */
/*   Updated: 2025/07/18 01:37:42 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

/**
 * create_token - create list and append the new node at the back
 * 
 * @tokens: the list of tokens
 * @type: type of the new token
 * @value: token value
 * 
 * Return: pointer to the new list , NULL if failed
 */

t_tokens	*create_token(t_tokens *tokens, char *value)
{
	t_tokens	*token;
	t_tokens	*temp;

	token = safe_malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free_collector_all(1);
		return (NULL);
	}
	token->segments = NULL;
	token->next = NULL;
	if (!tokens)
		return (token);
	temp = tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = token;
	return (tokens);
}

t_cmd	*add_cmd(t_cmd *head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!head)
		return (new_cmd);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
	return (head);
}

/**
 * add_redir - Add a new redirection node to the end of a redirection list
 * 
 * @head: Pointer to the head of the redirection list
 * @type: Type of the redirection
 * @flag: The filename or flag associated with the redirection
 *
 * Return: Pointer to the head ofredirection list, NULL on error
 */
t_reds	*add_redir(t_reds *head, t_types type, char *flag, int quoted)
{
	t_reds	*redir;
	t_reds	*current;

	redir = ft_calloc(1, sizeof(t_reds));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->flag = ft_strdup(flag);
	if (!redir->flag)
	{
		free_collector_all(1);
		return (NULL);
	}
	redir->quoted = quoted;
	redir->next = NULL;
	if (!head)
		return (redir);
	current = head;
	while (current->next)
		current = current->next;
	current->next = redir;
	return (head);
}

int	add_fields(t_tokens **tokens, char **fields, char *expanded)
{
	int	i;

	i = 0;
	while (fields && fields[i])
	{
		*tokens = create_token(*tokens, fields[i]);
		if (!*tokens)
		{
			free_collector_one(expanded);
			free_fields(fields);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	create_seg_token(t_tokens **tokens, t_segment *segments)
{
	t_tokens	*new_token;
	t_tokens	*current;

	new_token = safe_malloc(sizeof(t_tokens));
	if (!new_token)
		return (-1);
	new_token->segments = segments;
	new_token->type = WORD;
	new_token->next = NULL;
	new_token->value = NULL;
	if (!*tokens)
	{
		*tokens = new_token;
	}
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
	return (1);
}
