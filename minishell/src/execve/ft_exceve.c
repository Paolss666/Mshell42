/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:33:51 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 02:30:14 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

extern int	g_signal_received;

void	logic_parent(t_execve *pipex, t_file **temp)
{
	ms_signals();
	parent(pipex->fd, pipex->current_pipe, pipex);
	if (pipex->pipe_redirections)
	{
		temp = pipex->pipe_redirections[pipex->current_pipe];
		if (*temp && *temp)
			*temp = (*temp)->next;
		else
			*temp = NULL;
	}
}

void	in_logic_fork(t_cmd *new_to_pars, t_execve *pipex, t_file **temp,
		t_envp *enviroment)
{
	int	i;

	i = 0;
	if (pipex->pid[pipex->current_pipe] == -1)
		perror("fork error");
	if (pipex->pid[pipex->current_pipe] == 0)
	{
		set_signal_action(3);
		child(new_to_pars, pipex, i, enviroment);
	}
	else
		logic_parent(pipex, temp);
}

int	execute_pipeline_command(t_execve *pipex, t_cmd *new_to_pars,
		t_envp *enviroment)
{
	t_file	**temp;

	temp = NULL;
	if (pipex->n_pipe - 1 > 0)
	{
		if ((pipe(pipex->fd) == -1
				|| pipe(pipex->tmp_fd[pipex->current_pipe]) == -1))
			perror("pipe error");
	}
	pipex->pid[pipex->current_pipe] = fork();
	in_logic_fork(new_to_pars, pipex, temp, enviroment);
	return (0);
}

int	brain_execute_pipe_command(t_cmd *new_to_pars, t_execve *pipex,
		t_envp *enviroment)
{
	int	n;

	n = 0;
	while ((pipex && pipex->current_pipe < pipex->n_pipe && new_to_pars)
		|| (pipex && pipex->current_pipe < pipex->n_pipe && new_to_pars
			&& pipex->pipe_redirections[pipex->current_pipe]) || (pipex
			&& pipex->current_pipe < pipex->n_pipe && !new_to_pars
			&& pipex->pipe_redirections[pipex->current_pipe]))
	{
		if (execute_pipeline_command(pipex, new_to_pars, enviroment))
			n++;
		pipex->current_pipe++;
		if (new_to_pars && new_to_pars->next)
			new_to_pars = new_to_pars->next;
	}
	return (n);
}

int	ft_execve(t_cmd *to_pars, t_envp *enviroment, t_exp *export,
		int error_status)
{
	t_execve	*pipex;
	t_cmd		*new_to_pars;
	int			n;

	n = 0;
	if (!to_pars)
		return (0);
	new_to_pars = parsing_before_pipe_red(to_pars);
	pipex = init_structure(enviroment, new_to_pars, export, error_status);
	if (!pipex)
		return (1);
	pipex->cmd_err = NULL;
	pipex->cmd_err = copy_node(to_pars);
	new_to_pars = remove_redirections(new_to_pars);
	new_to_pars = parse_for_token(new_to_pars);
	pipex->for_h = len_liste_cmd(new_to_pars);
	n = brain_execute_pipe_command(new_to_pars, pipex, enviroment);
	logic_wait_pd(pipex, n);
	close_all_fd_tmp(pipex, n);
	if (g_signal_received == 60)
		return (error_status);
	error_status = pipex->error;
	return (pipex->error);
}
