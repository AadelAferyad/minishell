/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:13:01 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/22 17:12:25 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

# include "../libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct memory_system_managment
{
	unsigned int	size;
	void	*data;
	struct memory_system_managment	*next;
} collector;

extern collector	*head;

void	*safe_malloc(unsigned int size);
void	free_collector_one(void *add);
void	free_collector_all(void);

#endif




