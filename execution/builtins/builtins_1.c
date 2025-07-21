/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:18:39 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/21 21:33:22 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	change_env_list(t_env **head, t_env *tmp, char *buff, t_env *prev)
{
	t_env	*node;

	node = create_node_env(tmp->key, buff);
	if (tmp == *head)
	{
		*head = node;
		node->next = tmp->next;
	}
	else
	{
		prev->next = node;
		node->next = tmp->next;
	}
}

static int	change_pwd_helper(t_env **head, char *s, int len)
{
	char	*buff;
	t_env	*prev;
	t_env	*tmp;

	tmp = *head;
	prev = tmp;
	buff = getcwd(NULL, 0);
	if (!buff)
		return (ft_putstr_fd("cd: error retrieving current directory:\
				getcwd : cannot access parent directories:\
	       			No such file or directory\n", 2),
			g_structs.exit_status = 1, chdir("/home/"), 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, s, len))
		{
			change_env_list(head, tmp, buff, prev);
			free_node(tmp, buff);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	create_pwd(s, head, buff);
	return (1);
}

static int	change_pwd(char *s, int len)
{
	t_env	**head;

	head = get_env();
	return (change_pwd_helper(head, s, len));
}

static int	cd_helper(char **args, char *path)
{
	struct stat	st;

	if (args[1])
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (g_structs.exit_status = 1, 0);
	}
	if (access(path, F_OK) == 0)
	{
		stat(path, &st);
		if (S_ISDIR(st.st_mode))
		{
			if (!change_pwd("OLDPWD", 6))
				return (0);
		}
		else
			return (ft_putstr_fd("No such file or directory\n", 2),
				g_structs.exit_status = 1, 0);
	}
	else
		return (ft_putstr_fd("No such file or directory\n", 2),
			g_structs.exit_status = 1, 0);
	return (1);
}

int	builtin_cd(char **args)
{
	char	*path;

	path = args[0];
	if (!path || !path[0])
		return (0);
	if (!cd_helper(args, path))
		return (0);
	if (chdir(path) == 0)
		change_pwd("PWD", 3);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		g_structs.exit_status = 127;
	}
	g_structs.exit_status = 0;
	return (0);
}
