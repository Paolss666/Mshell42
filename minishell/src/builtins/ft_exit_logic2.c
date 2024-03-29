/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_logic2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:35:12 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/12 00:52:09 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

long long int	ft_atol(const char *nptr, int i, int parity, int *digit)
{
	long long int	number;

	number = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			parity++;
		i++;
	}
	while (nptr[i] == '0')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = 10 * number + nptr[i] - 48;
		(*digit)++;
		i++;
	}
	if (parity % 2 == 0)
		return (number);
	return (number * -1);
}

int	check_for_max_int(char *str)
{
	long long int	nb;
	int				i;
	int				parity;
	int				digit;	

	parity = 0;
	digit = 0;
	i = 0;
	nb = ft_atol(str, i, parity, &digit);
	if (digit > 19)
		return (1);
	if (nb < -9223372036854775807)
		return (1);
	if (nb > 9223372036854775807)
		return (1);
	return (0);
}

char	*ft_clean_exit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]) == 0)
	{
		if (str[i] == '-')
			str[0] = '-';
		str[i] = '0';
		i++;
	}
	return (str);
}

int	ft_exit_ls(t_cmd *to_pars)
{
	char	**split;

	split = NULL;
	if (to_pars->next)
	{
		split = ft_split_garbage(to_pars->next->cmd, ' ');
		if (split[1])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd("exit", 2);
			ft_putstr_fd(" : too many arguments \n", 2);
			return (1);
		}
	}
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(to_pars->next->cmd, 2);
	ft_putstr_fd(" numeric argument required\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit(2);
}

int	ft_exit_neg(t_cmd *to_pars)
{
	int		i;
	char	**tab;

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
