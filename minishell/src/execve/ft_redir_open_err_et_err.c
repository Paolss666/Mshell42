/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_open_err_et_err.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:51:19 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 13:52:59 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_error_not_found_directory(t_file *file_list, t_execve *pipex, int i)
{
	ft_putstr_fd("bash : ", 2),
	ft_putstr_fd(file_list->nome_file, 2);
	perror(" ");
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->tmp_fd[i][0]);
	close(pipex->tmp_fd[i][1]);
	garbagge(FLUSH, NULL, EX);
	garbagge(FLUSH, NULL, PARS);
	garbagge(FLUSH, NULL, ENV);
	exit(1);
}

void	ft_error_redir_file(int fd, t_execve *pipex, int i, t_cmd *to_pars)
{
	(void)i;
	(void)pipex;
	(void)pipex;
	if (fd == -1)
	{
		ft_putstr_fd("bash:", 2);
		ft_putstr_fd(to_pars->cmd, 2);
		ft_putstr_fd(to_pars->cmd, 2);
		perror(" ");
		close(fd);
		exit(1);
	}
}

void	ft_open_redir_in(t_file *file_list, t_execve *pipex, int i)
{
	int	fd_1;

	remove_q(file_list->nome_file);
	fd_1 = open(file_list->nome_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_1 == -1)
		return (ft_error_not_found_directory(file_list, pipex, i),
			(void)0);
	if (dup2(fd_1, 1) == -1)
		(perror("error dup1 open"), close(fd_1));
	close(fd_1);
}

void	ft_open_redir_out(t_file *file_list, t_execve *pipex, int i)
{
	int	fd_2;

	remove_q(file_list->nome_file);
	fd_2 = open(file_list->nome_file, O_RDONLY, 0666);
	if (fd_2 == -1)
		return (ft_error_not_found_directory(file_list, pipex, i), (void)0);
	if (dup2(fd_2, 0) == -1)
		(perror("error dup1 open"), close(fd_2));
	close(fd_2);
}

void	ft_open_redir_in_append(t_file *file_list, t_execve *pipex, int i)
{
	int	fd_1;

	remove_q(file_list->nome_file);
	fd_1 = open(file_list->nome_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_1 == -1)
		return (ft_error_not_found_directory(file_list, pipex, i),
			(void)0);
	if (dup2(fd_1, 1) == -1)
		(perror("error dup1 open"), close(fd_1));
	close(fd_1);
}
