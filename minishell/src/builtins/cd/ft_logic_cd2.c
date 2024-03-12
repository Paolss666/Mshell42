/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:14:48 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:06:38 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_home_not_found(char *home)
{
	if (!home)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd("cd :", 2);
		ft_putstr_fd("HOME not set\n", 2);
		return (2);
	}
	return (0);
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

void	found_pwd_in_env_modif(t_envp *enviroment, char *new_pwd)
{
	if (!enviroment || !new_pwd)
		return ((void)0);
	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "PWD") == 0)
			break ;
		enviroment = enviroment->next;
	}
	if (!enviroment)
		return ((void)0);
	enviroment->value = ft_strjoin("=", new_pwd);
	if (!enviroment->value || garbagge(ADD, enviroment->value, ENV))
		return ((void)0);
	enviroment->path = ft_strjoin(enviroment->name, enviroment->value);
	if (!enviroment->path || garbagge(ADD, enviroment->path, ENV))
		return (garbagge(FREE, enviroment->value, ENV), (void)0);
}
