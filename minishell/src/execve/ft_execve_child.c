/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 01:07:49 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 01:09:54 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	child_check_path_ifnt_error(t_cmd *new_to_pars, t_envp *enviroment,
		t_execve *pipex, char **tmp)
{
	int	j;

	j = 0;
	if (tmp && tmp[0] && ft_strcmp(tmp[0], "echo") && ft_strcmp(tmp[0], "env")
		&& ft_strcmp(tmp[0], "export") && ft_strcmp(tmp[0], "exit")
		&& ft_strcmp(tmp[0], "pwd") && ft_strcmp(tmp[0], "cd")
		&& ft_strcmp(tmp[0], "unset"))
	{
		pipex->get_g_path = ft_good_path_access(new_to_pars, enviroment, pipex);
		if (!pipex->get_g_path)
		{
			j = ft_error_commande_not_to_pars(new_to_pars, pipex);
			if (j)
			{
				close(pipex->fd[0]);
				close(pipex->fd[1]);
				close(pipex->tmp_fd[pipex->current_pipe][0]);
				close(pipex->tmp_fd[pipex->current_pipe][1]);
				(garbagge(FLUSH, NULL, ALL), exit(j));
			}
		}
	}
}

void	found_built_in_child(char **tmp, t_execve *pipex, t_cmd *new_to_pars,
		int j)
{
	if (tmp && tmp[0] && !ft_strcmp(tmp[0], "echo") && tmp[1]
		&& !ft_check_valid_flag_echo(tmp[1]))
		found_echo_in_pipe_flag(tmp + 1);
	if (tmp && tmp[0] && !ft_strcmp(tmp[0], "echo"))
		found_echo_in_pipe(new_to_pars);
	if (tmp && tmp[0] && !ft_strcmp(tmp[0], "env"))
		found_env_in_pipe(new_to_pars->cmd, pipex);
	if (tmp && tmp[0] && !ft_strcmp(tmp[0], "export") && !tmp[1])
		found_export_in_pipe(new_to_pars->cmd, pipex);
	else if (tmp && tmp[0] && !ft_strcmp(tmp[0], "export"))
		(garbagge(FLUSH, NULL, ALL), exit(0));
	if (tmp && tmp[0] && !ft_strcmp(tmp[0], "exit"))
		found_exit_in_pipe(new_to_pars);
	if (tmp && tmp[0] && !ft_strcmp(tmp[0], "pwd"))
		found_pwd_in_pipe(pipex);
	else if (!new_to_pars || !new_to_pars->cmd || !ft_strcmp(tmp[0], "unset")
		|| !ft_strcmp(tmp[0], "cd"))
		(garbagge(FLUSH, NULL, ALL), exit(0));
	else
		pass_execve(pipex->good_cmd, pipex->get_g_path, pipex, j);
}

void	built_in_child_execve(t_cmd *new_to_pars, t_execve *pipex, int j,
		t_envp *enviroment)
{
	char	**tmp;

	tmp = NULL;
	if (new_to_pars && new_to_pars->cmd)
	{
		tmp = ft_split_garbage_gogo(new_to_pars->cmd, ' ');
		if (!tmp)
			(garbagge(FLUSH, NULL, ALL), exit(99));
	}
	child_check_path_ifnt_error(new_to_pars, enviroment, pipex, tmp);
	if (pipex->n_pipe - 1 > 0)
		close_if_plus_zero(pipex);
	found_built_in_child(tmp, pipex, new_to_pars, j);
}

void	child(t_cmd *new_to_pars, t_execve *pipex, int i, t_envp *enviroment)
{
	char	*tmp;

	if (new_to_pars && new_to_pars->cmd)
	{
		tmp = ft_strdup(new_to_pars->cmd);
		if (!tmp || garbagge(ADD, tmp, PARS))
			return ((void)0);
		pipex->good_cmd = ft_split_garbage_gogo(new_to_pars->cmd, ' ');
		if (!pipex->good_cmd)
			return (perror("error split"), (void)0);
	}
	redirection(pipex->fd, pipex->current_pipe, pipex);
	built_in_child_execve(new_to_pars, pipex, i, enviroment);
}

void	parent(int *fd, int i, t_execve *pipex)
{
	if (i > 0)
	{
		close(pipex->tmp_fd[i - 1][0]);
		close(pipex->tmp_fd[i - 1][1]);
	}
	if (i < pipex->n_pipe - 1)
		close(fd[1]);
	if (pipex->n_pipe - 1 > 0)
	{
		close(fd[1]);
		close(fd[0]);
	}
}