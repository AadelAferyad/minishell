/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:46:07 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/07 14:30:01 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env()
{
	t_env	*tmp;

	tmp = g_structs.env;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(tmp->value, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

static void	change_pwd(char *s, int len)
{
	t_env	*tmp;

	tmp = g_structs.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, s, len))
		{
			free_collector_one(tmp->value);
			tmp->value = getcwd(NULL, 0);
			printf("inside changing pwd : %s = %s\n", tmp->key, tmp->value);
			add_node(tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("NOt found OLDPWD\n", 1);
}

int	builtin_cd(char *path)
{
	struct stat	st;

	if (!path || !path[0])
		return (0);
	if (access(path, F_OK) == 0)
	{
		stat(path, &st);
		if (S_ISDIR(st.st_mode))
			change_pwd("OLDPWD", 6);
	}
	if (chdir(path) == 0)
		change_pwd("PWD", 3);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
	}
	return (0);
}

/*
 * builtin_pwd - prints the fill name of the current working directory
 * @fd: integer file descriptor
 * */
int	builtin_pwd()
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	return (0);
}

/*
 * builtin_echo - Echo (print) the string to file ddescriptor
 * @args: double pointer points to the arguments the echo will print
 * */ 
int	builtin_echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!args[0])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
