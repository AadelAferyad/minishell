/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:13:01 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/24 11:51:39 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

# include "../libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct memory_system_managment
{
	bool					flag;
	void					*data;
	struct memory_system_managment	*next;
}	t_collector;

void	*safe_malloc(unsigned int size);
void	free_collector_one(void *add);
void	free_collector_all(void);

#endif




