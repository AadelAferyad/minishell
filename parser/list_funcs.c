/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:01:37 by imellali          #+#    #+#             */
/*   Updated: 2025/06/22 15:00:53 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_list(t_tokens **head)
{
	t_tokens	*temp;

	while (*head)
	{
		temp = *head;
		*head = temp->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	*head = NULL;
}

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

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
		return (NULL);
	token->next = NULL;
	if (!tokens)
		return (token);
	temp = tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = token;
	return (tokens);
}
