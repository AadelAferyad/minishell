/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:13:01 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/25 16:21:38 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

# include "../libft/libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct memory_system_managment
{
	void							*data;
	struct memory_system_managment	*next;
}									t_collector;

void								*safe_malloc(unsigned int size);
void								free_collector_one(void *add);
void								free_collector_all(int flaged);
void								free_env(void);

#endif
