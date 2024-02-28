/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:29:14 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/27 12:32:59 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE PWD */
// CA MARCHE PAS
// PWD NE PRENDES PAS DES ARGUMETNS ---//
// EX; 	PWD ASDASDAS	-----> MEGGAGE D'ERREUR => pwd: too many arguments
// il doit avoir que pwd dans les argv;

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
				ft_putstr_fd("shell-init: error retrieving current directory: No such file or directory\n", 2);
			else
				printf("%s\n", get_pwd);
			break ;
		}
		break ;
		to_pars = to_pars->next;
	}
	return (0);
}
