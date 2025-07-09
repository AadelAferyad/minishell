/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:35:02 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/09 13:03:44 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

	if (!add)
		return (NULL);
	node = create_node();
	if (!node)
		return (NULL);
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
	void	*tmp;

	ptr = malloc(size);
	if (!ptr)
	{
		free_collector_all(0);
		strerror(errno);
		exit(1);
	}
	tmp = add_node(ptr);
	if (!tmp)
	{
		free_collector_all(0);
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
	prev = NULL;
	while (tmp)
	{
		if (tmp->data == add)
		{
			if (prev)
				prev->next = tmp->next;
			else
				g_structs.collector = tmp->next;
			free(tmp->data);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	free_env(void)
{
	t_env	**head;
	t_env	*tmp;
	t_env	*ptr;

	head = get_env();
	tmp = *head;
	while (tmp)
	{
		ptr = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = ptr;
	}
	head = NULL;
}

/*
 * free_collector_all - frees all the noode and data that holeds
 * */

void	free_collector_all(int	flaged)
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
	if (!flaged)
	{
		free_env();
	}
	g_structs.cmd = NULL;
	g_structs.collector = NULL;
}
