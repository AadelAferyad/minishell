/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:48:47 by imellali          #+#    #+#             */
/*   Updated: 2025/07/18 01:55:25 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tokens	*cleanup(void)
{
	free_collector_all(1);
	return (NULL);
}

t_tokens	*lexer_cleanup(void)
{
	return (cleanup());
}
