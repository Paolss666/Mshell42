/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:28:46 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 17:31:09 by npaolett         ###   ########.fr       */
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
	if (check_for_max_int(str))
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

int	too_many_args(t_cmd *to_pars)
{
	if (ft_is_valid_number(to_pars->next->cmd))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: ", 2);
		if (to_pars->next->cmd)
			remove_quote(to_pars->next->cmd);
		ft_putstr_fd(to_pars->next->cmd, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		garbagge(FLUSH, NULL, ALL);
		exit(2);
	}
}

int	exit_process(t_cmd *to_pars)
{
	int	return_value;

	return_value = 0;
	remove_quote(to_pars->next->cmd);
	if (ft_is_valid_number(to_pars->next->cmd))
	{
		ft_putstr_fd("exit\n", 1);
		to_pars->next->cmd = ft_clean_exit(to_pars->next->cmd);
		if (atoi(to_pars->next->cmd) < 0)
		{
			return_value = ft_atoi(to_pars->next->cmd);
			if (return_value == 0)
				exit(0);
			garbagge(FLUSH, NULL, ALL);
			exit((256 + return_value) % 256);
		}
		return_value = ft_atoi(to_pars->next->cmd);
		garbagge(FLUSH, NULL, ALL);
		exit((return_value % 256));
	}
	else
		return (ft_exit_ls(to_pars));
	return (0);

}

int	ft_exit(t_cmd *to_pars, t_envp *env, t_exp *exp)
{
	int	i;

	i = 0;
	found_shlv_exit(env, exp);
	remove_quote(to_pars->cmd);
	if (!ft_strncmp("exit -", to_pars->cmd, 6))
		i = ft_exit_neg(to_pars);
	else
	{
		if (!ft_strcmp(to_pars->cmd, "exit") && !to_pars->next)
		{
			ft_putstr_fd("exit\n", 1);
			garbagge(FLUSH, NULL, ALL);
			exit(0);
		}
		if (to_pars && to_pars->next && to_pars->next->next)
			i = too_many_args(to_pars);
		else if (!ft_strcmp("exit", to_pars->cmd) && to_pars->next)
			i = exit_process(to_pars);
	}
	return (i);
}
