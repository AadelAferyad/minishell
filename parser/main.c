/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:17:44 by imellali          #+#    #+#             */
/*   Updated: 2025/06/20 17:26:22 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
