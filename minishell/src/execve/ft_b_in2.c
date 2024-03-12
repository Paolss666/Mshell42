/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_b_in2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:18:45 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:21:00 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_err_to_not_numb(char *exit_r)
{
	ft_putstr_fd("bash: exit :", 2);
	ft_putstr_fd(exit_r, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit(2);
}

void	found_exit_in_pipe(t_cmd *ntp)
{
	char	**exit_n;
	int		n;

	n = 0;
	exit_n = ft_split_garbage(ntp->cmd, ' ');
	if (!exit_n)
		exit(99);
	if (exit_n[1])
	{
		if (exit_n[2])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			garbagge(FLUSH, NULL, ALL);
			exit(2);
		}
		if (check_for_max_int(exit_n[1]))
			print_err_to_not_numb(exit_n[1]);
		if (!if_not_numeric(exit_n[1]))
			print_err_to_not_numb(exit_n[1]);
		n = ft_atoi(exit_n[1]);
		garbagge(FLUSH, NULL, ALL);
		exit((256 + n) % 256);
	}
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}

void	found_export_in_pipe(char *cmd, t_execve *pipe)
{
	char	*error;

	error = ft_substr(cmd, 4, ft_strlen(cmd));
	if (!error || garbagge(ADD, error, EX))
		return ;
	if (!ft_strcmp(cmd, "export"))
		print_env_array(pipe->exp);
	else if (!ft_strncmp(cmd, "export ", 4))
	{
		garbagge(FLUSH, NULL, ALL);
		exit(1);
	}
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}

void	found_env_in_pipe(char *cmd, t_execve *pipe)
{
	char	*error;

	error = ft_substr(cmd, 4, ft_strlen(cmd));
	if (!error || garbagge(ADD, error, EX))
		return ;
	if (!ft_strcmp(cmd, "env"))
		print_env_array(pipe->new_enviroment);
	else if (!ft_strncmp(cmd, "env ", 4))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd(" :not such a file or directory\n", 2);
	}
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}

int	found_in_to_pars(t_cmd *current)
{
	if (ft_strncmp(current->cmd, "<", 1) == 0 || ft_strncmp(current->cmd, ">",
			1) == 0 || ft_strncmp(current->cmd, ">>", 2) == 0
		|| ft_strncmp(current->cmd, "<<", 2) == 0)
		return (0);
	return (1);
}
