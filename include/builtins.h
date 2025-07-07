/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:16:05 by aaferyad          #+#    #+#             */
/*   Updated: 2025/06/26 15:24:14 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>

int	builtin_echo(char **arg);
int	builtin_pwd(void);
int	builtin_cd(char *path);
void	builtin_env(void);

#endif
