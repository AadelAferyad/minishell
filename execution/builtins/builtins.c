/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:46:07 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/09 12:37:22 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env()
{
	t_env	*tmp;

	tmp = *get_env();
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_structs.exit_status = 0;
}

t_env	*create_node_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->key = _strdup(key);
	node->value = _strdup(value);
	node->next = NULL;
	if (!node || !node->key || !node->value)
	{
		free_collector_all(0);
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	return (node);
}


static void	change_pwd(char *s, int len)
{
	t_env	*tmp;
	t_env	**head;
	t_env	*prev;
	t_env	*node;
	char	*buff;

	head = get_env();
	tmp = *head;
	prev = tmp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, s, len))
		{
			buff = getcwd(NULL, 0);
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
			free(buff);
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	buff = getcwd(NULL, 0);
	node = create_node_env(s, buff);
	node->next = *head;
	(*head) = node;
	free(buff);
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
	else
	{
		g_structs.exit_status = 1;
		return (1);
	}
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
	g_structs.exit_status = 0;
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
		g_structs.exit_status = 0;
		return (0);
	}
	while (args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
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
	g_structs.exit_status = 0;
	return (0);
}

void	print_export()
{
	t_env	*tmp;

	tmp = *get_env();
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_structs.exit_status = 0;
}

t_env	*does_node_exists(char *key, int size)
{
	t_env	*node;

	node = *get_env();
	while (node)
	{
		if (!ft_strncmp(key, node->key, size))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	add_node_to_env(char *key, char *value)
{
	t_env	*node;
	t_env	**head;

	head = get_env();
	node = does_node_exists(key, ft_strlen(key));
	if (node)
	{
		free(node->value);
		node->value = _strdup(value);
	}
	else
	{
		node = create_node_env(key, value);
		node->next = *head;
		*head = node;
	}
}

void	builtin_unset(char *args)
{
	t_env	**head;
	t_env	*node;
	t_env	*tmp;
	int	size;

	head = get_env();
	node = *head;
	g_structs.exit_status = 0;
	if (!args)
		return ;
	size = ft_strlen(args);
	while (node)
	{
		if (!ft_strncmp(args, node->key, size))
		{
			if (node == *head)
			{
				*head = node->next;
			}
			else
				tmp->next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			break ;
		}
		tmp = node;
		node = node->next;
	}
}

void	builtin_export(char **args)
{
	int	i;
	char	*key;
	char	*value;

	i = 0;
	if (!args[0])
	{
		print_export();
		return ;
	}
	while (args[0][i] && args[0][i] != '=')
	{
		if (ft_isdigit(args[0][0]) || !ft_isalnum(args[0][i]))
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			g_structs.exit_status = 1;
			return ;
		}
		i++;
	}
	if (!args[0][i])
		return ;
	key = ft_substr(args[0], 0, i);
	if (!args[1])
		value = ft_strdup("");
	else
		value = ft_strdup(args[1]);
	add_node_to_env(key, value);
	free_collector_one(key);
	free_collector_one(value);
	g_structs.exit_status = 0;
}
