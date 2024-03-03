/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:28:46 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/03 08:38:51 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


int	ft_is_valid_number(char *str)
{
	if (!has_number(str))
		return (0);
	if (!before_num_is_right(str))
		return (0);
	if (after_num_is_right(str) == 0)
		return (0);
	return (1);
}

int	found_exit(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "exit", 4) == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

void	too_many_args(t_cmd *to_pars)
{
	if (ft_is_valid_number(to_pars->next->cmd))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd(to_pars->next->cmd, 2);
		ft_putstr_fd("bash: numeric argument required\n", 2);
		garbagge(FLUSH, NULL, ALL);
		exit(2);
	}
}

void	exit_process(t_cmd *to_pars)
{
	int	return_value;

	return_value = 0;
	if (ft_is_valid_number(to_pars->next->cmd))
	{
		ft_putstr_fd("exit\n", 1);
		to_pars->next->cmd = ft_clean_exit(to_pars->next->cmd);
		if (atoi(to_pars->next->cmd) < 0)
		{
			return_value = atoi(to_pars->next->cmd);
			garbagge(FLUSH, NULL, ALL);
			exit((256 + return_value) % 256);
		}
		return_value = atoi(to_pars->next->cmd);
		garbagge(FLUSH, NULL, ALL);
		exit((return_value % 256));
	}
	else
		ft_exit_ls(to_pars);
}

void	ft_exit(t_cmd *to_pars, t_envp *env, t_exp *exp)
{
	found_shlv_exit(env, exp);
	if (!ft_strncmp("exit -", to_pars->cmd, ft_strlen("exit -")))
		ft_exit_neg(to_pars);
	else
	{
		if (!ft_strcmp(to_pars->cmd, "exit") && !to_pars->next)
		{
			ft_putstr_fd("exit\n", 1);
			garbagge(FLUSH, NULL, ALL);
			exit(0);
		}
		if (to_pars && to_pars->next && to_pars->next->next)
			too_many_args(to_pars);
		else if (!ft_strcmp("exit", to_pars->cmd) && to_pars->next)
			exit_process(to_pars);
	}
}
