/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:54:39 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 00:57:48 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_directory(char *s)
{
	DIR	*dir;

	dir = opendir(s);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

void	ft_error_commande_split(char *cmd)
{
	ft_putstr_fd("bash : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return ;
}

void	ft_error_quotes(t_execve *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			ft_putstr_fd("bash : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			pipex->error = 126;
			return ;
		}
		else
		{
			ft_putstr_fd("bash : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			pipex->error = 127;
			return ;
		}
	}
	ft_putstr_fd("bash : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	pipex->error = 127;
	return ((void)0);
}

void	ft_error_single_quotes(t_execve *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			ft_putstr_fd("bash : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			pipex->error = 126;
			return ;
		}
		else
		{
			ft_putstr_fd("bash : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			pipex->error = 127;
			return ;
		}
	}
	ft_putstr_fd("bash : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	pipex->error = 127;
	return ((void)0);
}

int	logic_split_for_commande(char *cmd, t_execve *pipex)
{
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			ft_putstr_fd("bash : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return (126);
		}
		else
		{
			ft_putstr_fd("bash : ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			pipex->error = 127;
		}
	}
	else
	{
		ft_putstr_fd("bash : ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (127);
}
