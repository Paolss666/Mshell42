/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:54:39 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/08 17:31:44 by npaolett         ###   ########.fr       */
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
		if(is_directory(cmd))
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
		if(is_directory(cmd))
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

int	check_for_logic_err(t_execve *pipex, t_cmd *to_pars, char **cmd)
{
	if (!to_pars->cmd)
	{
		ft_error_commande_split(cmd[0]);
		pipex->error = 127;
		return (pipex->error);
	}
	else if (to_pars->cmd && ft_strchr(to_pars->cmd, '\"'))
	{
		ft_error_quotes(pipex, cmd[0]);
		return (pipex->error) ;
	}
	else if (to_pars->cmd && ft_strchr(to_pars->cmd, '\''))
	{
		ft_error_single_quotes(pipex, cmd[0]);
		return (pipex->error);
	}
	pipex->error = logic_split_for_commande(cmd[0], pipex);
	return (pipex->error);
}

int	ft_error_commande_not_to_pars(t_cmd *to_pars, t_execve *pipex)
{
	char	**cmd;
	char	*err;

	pipex->error = 127;
	if (pipex->token)
		err = to_pars->cmd;
	else
		err = pipex->cmd_err->cmd;
	printf("ft_error_commande_not_to_pars\n");
	cmd = ft_split_garbage_gogo(err, ' ');
	// cmd = ft_split_garbage(err, ' ');
	if (!cmd)
		return (garbagge(FLUSH, NULL, ALL), exit (10), 0);
	// if (ft_strchr(err, '\'') || ft_strchr(err, '\"'))
	// 	split_by_quotes_and_spaces(err, cmd, 0);
	if (ft_strcmp(err, " ") == 0)
	{
		ft_putstr_fd("bash : ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": command not found\n", 2);	
		pipex->error = 127;
		return (pipex->error);
	}
	pipex->error = check_for_logic_err(pipex, to_pars, cmd);
	return (pipex->error);
}
