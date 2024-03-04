/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_in_out.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:19:32 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/04 00:57:02 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"



void ft_error_not_found_directory(t_file *file_list, t_execve *pipex, int i)
{
	ft_putstr_fd("bash : ", 2),
	ft_putstr_fd(file_list->nome_file, 2);
	perror(" ");
	(void)i;
	(void)pipex;
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
	int fd_1;

	fd_1 = open(file_list->nome_file, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
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

	fd_1 = open(file_list->nome_file, O_WRONLY | O_CREAT | O_APPEND,
			0666);
	if (fd_1 == -1)
		return (ft_error_not_found_directory(file_list, pipex, i),
			(void)0);
	if (dup2(fd_1, 1) == -1)
		(perror("error dup1 open"), close(fd_1));
	close(fd_1);
}


void	ft_open_redir_here_doc(t_file *file_list, t_execve *pipex, int i)
{
	int	fd_1;

	fd_1 = 0;
	if (file_list->here_doc_fd != -1)
	{
		fd_1 = open(file_list->here_doc, O_RDONLY, 0666);
		if (fd_1 == -1)
			return (ft_error_not_found_directory(file_list, pipex, i), (void)0);
		if (dup2(fd_1, 0) == -1)
			(perror("error here open"), close(fd_1));
		close(fd_1);
		unlink(file_list->here_doc);
	}
}

void	redirection_simple1(int *fd, int i, t_execve *pipex)
{
	close(fd[1]);
	if (dup2(pipex->tmp_fd[i][1], 1) == -1)
		(perror("error dup1 open"), close(pipex->tmp_fd[i][1]));
	close(fd[0]);
	close(pipex->tmp_fd[i][0]);
	close(pipex->tmp_fd[i][1]);
}

void	redirection_simple(int *fd, int i, t_execve *pipex)
{
	close(fd[0]);
	if (dup2(pipex->tmp_fd[i - 1][0], 0) == -1)
		(perror("error dup open"), close(pipex->tmp_fd[i - 1][0]));
	close(fd[1]);
	close(pipex->tmp_fd[i - 1][0]);
	close(pipex->tmp_fd[i - 1][1]);
}

void	close_all_fd(int *fd, t_execve *pipex, int i)
{
	close(fd[1]);
	close(fd[0]);
	close(pipex->tmp_fd[i][0]);
	close(pipex->tmp_fd[i][1]);
}

void	redirection(int *fd, int i, t_execve *pipex)
{
	t_file	*fileList;

	fileList = NULL;
	if (i > 0)
		redirection_simple(fd, i, pipex);
	if (i < pipex->n_pipe - 1)
		redirection_simple1(fd, i, pipex);
	if (pipex->pipe_redirections[i] && *pipex->pipe_redirections[i])
	{
		fileList = *pipex->pipe_redirections[i];
		while (fileList)
		{
			if (ft_strcmp(fileList->redir, ">") == 0)
				ft_open_redir_in(fileList, pipex, i);
			else if (ft_strcmp(fileList->redir, "<") == 0)
				ft_open_redir_out(fileList, pipex, i);
			else if (ft_strcmp(fileList->redir, ">>") == 0)
				ft_open_redir_in_append(fileList, pipex, i);
			else if (ft_strcmp(fileList->redir, "<<") == 0)
				ft_open_redir_here_doc(fileList, pipex, i);
			if (fileList)
				fileList = fileList->next;
		}
	}
}
