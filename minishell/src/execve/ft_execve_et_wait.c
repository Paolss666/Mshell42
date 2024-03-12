/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_execve3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:25:37 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:30:15 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	found_count_pipe(t_cmd *cmd)
{
	int		pipe_count;
	char	*str;
	int		flag;

	pipe_count = 0;
	flag = 0;
	while (cmd != NULL)
	{
		str = cmd->cmd;
		while (*str != '\0')
		{
			if (*str == '\'' || *str == '\"')
				flag = !flag;
			if (*str == '|' && flag == 0)
				pipe_count++;
			str++;
		}
		cmd = cmd->next;
	}
	return (pipe_count);
}

void	creation_cmd_empty(t_cmd **current_commande, const char *new_cmd)
{
	t_cmd	*new_node;
	t_cmd	*temp;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node || garbagge(ADD, new_node, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
	new_node->next = NULL;
	if (new_cmd)
	{
		new_node->cmd = ft_strdup(new_cmd);
		if (!new_node->cmd || garbagge(ADD, new_node->cmd, PARS))
			(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
	}
	else
		new_node->cmd = NULL;
	if (*current_commande == NULL)
		*current_commande = new_node;
	else
	{
		temp = *current_commande;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	close_all_fd_tmp(t_execve *pipex, int n)
{
	if (!pipex)
		return ((void)0);
	pipex->current_pipe = 1;
	while (pipex->current_pipe < pipex->n_pipe - n
		&& pipex->pid[pipex->current_pipe])
	{
		close(pipex->tmp_fd[pipex->current_pipe][1]);
		close(pipex->tmp_fd[pipex->current_pipe][0]);
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		pipex->current_pipe++;
	}
}

void	pass_execve(char **good_commande, char *get_good_path, t_execve *pipex,
		int i)
{
	if (i)
	{
		garbagge(FLUSH, NULL, ALL);
		exit(1);
	}
	if (execve(get_good_path, good_commande, pipex->new_enviroment) == -1)
	{
		perror("execve error");
		garbagge(FLUSH, NULL, ALL);
		exit(1);
	}
}

void	logic_wait_pd(t_execve *pipex, int n)
{
	int	status;
	int	i;

	i = 0;
	if (!pipex)
		return ;
	while (i < pipex->n_pipe - n && pipex->pid[i])
	{
		if (waitpid(pipex->pid[i], &status, 0) == -1)
			perror("waitpid error");
		else
		{
			if (WIFEXITED(status))
				pipex->error = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				pipex->error = WTERMSIG(status) + 128;
				if (pipex->error == 130)
					printf("\n");
				if (pipex->error == 131)
					printf("Quit (core dumped)\n");
			}
		}
		i++;
	}
}