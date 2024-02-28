/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:14:48 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:15:51 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_home_not_found(char *home)
{
	if (!home)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd("cd :", 2);
		ft_putstr_fd("HOME not set\n", 2);
	}
}

char	*home_found(char *home)
{
	home = ft_substr(home, ft_strlen("HOME="), ft_strlen(home));
	if (!home || garbagge(ADD, home, ENV))
		return (perror("fail ft_substr"), NULL);
	return (home);
}

char	*old_pwd_not_found(char *pwd, t_envp *enviroment, t_exp *export)
{
	char	*old_pwd;

	perror("fail chdir cd -");
	old_pwd = ft_strdup(pwd);
	if (!old_pwd || garbagge(ADD, old_pwd, PARS))
		return (NULL);
	change_env_export_old_pwd(enviroment, export, old_pwd);
	return (old_pwd);
}