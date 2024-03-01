/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_logic2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:35:12 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/01 17:06:38 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

void	ft_exit_ls(t_cmd *to_pars)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("exit: ", 2);
	remove_q(to_pars->next->cmd);
	ft_putstr_fd(to_pars->next->cmd, 2);
	ft_putstr_fd(" numeric argument required\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit(2);
}
