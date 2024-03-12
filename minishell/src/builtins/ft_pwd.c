/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:29:14 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:54:42 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_pwd(t_cmd *to_pars)
{
	char	*get_pwd;

	get_pwd = NULL;
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "pwd") == 0)
		{
			get_pwd = getcwd(NULL, 0);
			if (!get_pwd || garbagge(ADD, get_pwd, ENV))
			{
				ft_putstr_fd("pwd: erreur : getcwd", 2);
				ft_putstr_fd(" current \n", 2);
			}
			else
				printf("%s\n", get_pwd);
		}
		break ;
		to_pars = to_pars->next;
	}
	return (0);
}
