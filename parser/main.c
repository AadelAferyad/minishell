/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:17:44 by imellali          #+#    #+#             */
/*   Updated: 2025/06/21 14:39:27 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isspace(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	ft_isop(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
int	ft_isdouble_op(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return (1);
	else if (input[0] == '>' && input[1] == '>')
		return (1);
	return (0);
}

void	free_list(t_tokens **head)
{
	t_tokens	*temp;

	while (*head)
	{
		temp = *head;
		*head = temp->next;
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
 * return: pointer to the new list , NULL if failed
 */

t_tokens	*create_token(t_tokens *tokens, t_types type, char *value)
{
	t_tokens	*new_token;
	t_tokens	*temp;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
		return (NULL);
	new_token->next = NULL;
	if (!tokens)
		return (new_token);
	temp = tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	return (tokens);
}

/**
 * lexer - split the input string into tokens
 *
 * @input: the user input which is the command passed by user 
 * 
 * return: list that contain splitted tokens , NULL if failed
 */

t_tokens	*lexer(char *input)
{
	t_tokens	*tokens;
	int			i;
	int			start;
	char		*word;
	char		*operator;

	tokens = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		/* handling double operators*/
		if (input[i + 1] && ft_isdouble_op(input + i))
		{
			operator= ft_substr(input, i, 2);
			if (!operator)
				return (NULL);
			tokens = create_token(tokens, OP, operator);
			if (!tokens)
			{
				free(operator);
				free_list(&tokens);
				return (NULL);
			}
			free(operator);
			i += 2;
			continue ;
		}
		/* handling single operator*/
		if (ft_isop(input[i]))
		{
			operator= ft_substr(input, i, 1);
			if (!operator)
				return (NULL);
			tokens = create_token(tokens, OP, operator);
			if (!tokens)
			{
				free(operator);
				free_list(&tokens);
				return (NULL);
			}
			free(operator);
			i++;
			continue ;
		}
		/* skipping spaces */
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		/* handling words */
		start = i;
		while (input[i] && !ft_isop(input[i]) && !ft_isspace(input[i]))
			i++;
		word = ft_substr(input, start, i - start);
		if (!word)
		{
			free_list(&tokens);
			return (NULL);
		}
		tokens = create_token(tokens, WORD, word);
		if (!tokens)
		{
			free(word);
			free_list(&tokens);
			return (NULL);
		}
		free(word);
	}
	return (tokens);
}

int	main(void)
{
	char	*input;
	size_t	n;
	ssize_t	nread;

	n = 444;
	input = malloc(sizeof(char) * n);
	if (!input)
		return (-1);
	nread = getline(&input, &n, stdin);
	if (nread == -1)
		return (-1);
	printf("Command : %s\n", input);
	free(input);
	return (0);
}
