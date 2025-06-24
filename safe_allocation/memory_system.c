/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:35:02 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/24 11:54:38 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

t_collector	*create_node()
{
	return (malloc(sizeof(t_collector)));
}

/*
 * add_node - add new node the the collector to keep track of the allocated memory
 * @add: void pointer holds address of memory to be added to the collector
 * */

t_collector	*add_node(void *add)
{
	t_collector	*node;

	node = create_node();
	if (!node)
		return (NULL);
	node->flag = 0;
	node->next = g_structs.collector;
	node->data = add;
	g_structs.collector = node;
	return (node);
}

/*
 * safe_mallloc - allocate size of bytes and keep track of all the allocated memory on linked list
 * @size: size of bytes to be allocated
 * Return: returns allocated address generic pointer
 * */

void	*safe_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!add_node(ptr) || !ptr)
	{
		free_collector_all();
		strerror(errno);
		exit(1);
	}
	return (ptr);
}

/*
 * free_collector_one - frees the node that holeds memory for add
 * @add: void pointer that holeds address of tha memory to be freed.
 * */

void	free_collector_one(void *add)
{
	t_collector	*tmp;
	t_collector	*prev;

	tmp = g_structs.collector;
	prev = tmp;
	while (tmp)
	{
		if (tmp->data == add)
		{
			if (g_structs.collector == tmp)
				g_structs.collector = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->data);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/*
 * free_collector_all - frees all the noode and data that holeds
 * */

void	free_collector_all(void)
{
	t_collector	*tmp;
	t_collector	*head;

	head = g_structs.collector;
	while (head)
	{
		tmp = head->next;
		free(head->data);
		free(head);
		head = tmp;
	}
}

