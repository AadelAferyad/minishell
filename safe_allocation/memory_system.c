/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:35:02 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/22 17:14:28 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <collector.h>

collector	*head;

collector	*create_node()
{
	return (malloc(sizeof(collector)));
}

/*
 * add_node - add new node the the collector to keep track of the allocated memory
 * @add: void pointer holds address of memory to be added to the collector
 * */

collector	*add_node(void *add)
{
	collector	*node;

	node = create_node();
	if (!node)
		return (NULL);
	node->next = head;
	node->data = add;
	head = node;
	return (node);
}

/*
 * safe_mallloc - allocate size of bytes and keep track of all the allocated memory on linked list
 * @size: size of bytes to be allocated
 * Return: returns allocated address generec pointer
 * */

void	*safe_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	add_node(ptr);
	return (ptr);
}

/*
 * free_collector_one - frees the node that holeds memory for add
 * @add: void pointer that holeds address of tha memory to be freed.
 * */

void	free_collector_one(void *add)
{
	collector	*tmp;
	collector	*prev;

	tmp = head;
	prev = tmp;
	while (tmp)
	{
		if (tmp->data == add)
		{
			if (head == tmp)
				head = tmp->next;
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
	collector	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->data);
		free(head);
		head = tmp;
	}
}

