/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:14:14 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/11 17:25:06 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	has_number(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			flag = 1;
		i++;
	}
	return (flag);
}

int	before_num_is_right(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	if (ft_isdigit(str[i]) == 0)
		return (0);
	return (1);
}

int	after_num_is_right(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]) == 0)
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	too_much_arg_neg(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: exit: too many arguments\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit(2);
}

int	check_plus_arg_neg(void)
{
	ft_putstr_fd("exit: \n", 2);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("exit:", 2);
	ft_putstr_fd(" : too many arguments \n", 2);
	return (1);
}

void	err_neg_max_int(char *cmd)
{
	ft_putstr_fd("exit: \n", 2);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit(2);
}

int	ft_exit_neg(t_cmd *to_pars)
{
	int				i;
	char			**tab;

	i = 1;
	tab = ft_split_garbage_gogo(to_pars->cmd, ' ');
	while (tab[1][i] != '\0')
	{
		if (tab[2] || to_pars->next)
			if (check_plus_arg_neg())
				return (1);
		if (ft_isdigit(tab[1][i]) == 0 || check_for_max_int(tab[1]))
			err_neg_max_int(to_pars->cmd);
		i++;
	}
	i = atoi(tab[1]);
	if (to_pars->next)
		too_much_arg_neg();
	ft_putstr_fd("exit\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit((256 + i) % 256);
	return (0);
}
