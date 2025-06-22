/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:46:07 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/22 17:17:33 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	builtin_cd(char *path)
{
	struct stat	st;

	stat(path, &st);
	if (S_ISDIR(st.st_mode))
	{
		// change OLDPWD in env
	}
	if (chdir(path) != 0)
	{
	return (0);
}

/*
 * builtin_pwd - prints the fill name of the current working directory
 * @fd: integer file descriptor
 * */
int	builtin_pwd(int fd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, fd);
	ft_putchar_fd('\n', fd);
	free(cwd);
	return (0);
}

/*
 * builtin_echo - Echo (print) the string to file ddescriptor
 * @args: double pointer points to the arguments the echo will print
 * @fd: integer file descriptor
 * */ 
int	builtin_echo(char **args, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		i++;
		if (args[i])
			ft_putchar_fd(' ', fd);
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
