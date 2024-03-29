/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_in_out.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:19:32 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 23:11:35 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
		if (pipex->for_h == 2 && pipex->n_pipe - 1)
		{
			close(fd_1);
			unlink(file_list->here_doc);
			garbagge(FLUSH, NULL, ALL);
			exit(1);
		}
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
	t_file	*file_list;

	file_list = NULL;
	if (i > 0)
		redirection_simple(fd, i, pipex);
	if (i < pipex->n_pipe - 1)
		redirection_simple1(fd, i, pipex);
	if (pipex->pipe_redirections[i] && *pipex->pipe_redirections[i])
	{
		file_list = *pipex->pipe_redirections[i];
		while (file_list)
		{
			if (ft_strcmp(file_list->redir, ">") == 0)
				ft_open_redir_in(file_list, pipex, i);
			else if (ft_strcmp(file_list->redir, "<") == 0)
				ft_open_redir_out(file_list, pipex, i);
			else if (ft_strcmp(file_list->redir, ">>") == 0)
				ft_open_redir_in_append(file_list, pipex, i);
			else if (ft_strcmp(file_list->redir, "<<") == 0)
				ft_open_redir_here_doc(file_list, pipex, i);
			if (file_list)
				file_list = file_list->next;
		}
	}
}
