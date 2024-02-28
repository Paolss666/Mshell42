/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:28:46 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/27 12:29:09 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	found_exit(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "exit") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}


void	ft_exit(t_cmd *to_pars)
{
	if (!to_pars->next)
	{
		ft_putstr_fd("exit\n", 1);
		garbagge(FLUSH, NULL, ALL);
		exit(0);
	}
	if (!ft_is_all_digit(to_pars->next->cmd))
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
	else
	{
		if (to_pars->next->next)
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
		else
		{
			ft_putstr_fd("exit\n", 1);
			garbagge(FLUSH, NULL, ALL);
			exit(ft_atoi(to_pars->next->cmd) % 256);
		}
	}
}
