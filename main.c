/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:15:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/24 11:55:30 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

t_global	g_structs;

int	main(int ac, char **av, char **env)
{
	char	*s;
	char	*s1;
	char	**arr;
	int	*j;

	g_structs.collector = NULL;

	s = safe_malloc(sizeof(char) * 10);
	s1 = safe_malloc(sizeof(char) * 10);
	arr = safe_malloc(sizeof(char *) * 10);
	j = safe_malloc(sizeof(int));
	*j = 0;
	for (; *j < 9; *j = *j + 1)
	{
		arr[*j] = safe_malloc(sizeof(char) * 10);
		ft_strlcpy(arr[*j], "hello\n", 10);
	}
	arr[*j] = NULL;
	*j = 0;
	while (arr[*j])
	{
		ft_putstr_fd(arr[*j], 1);
		*j = *j + 1;
	}
	ft_strlcpy(s, "allah\n", 7);
	ft_strlcpy(s1, "allah s1\n", 9);
	ft_putstr_fd(s, 1);
	ft_putstr_fd(s1, 1);
	free_collector_all();	
	return (0);
}
