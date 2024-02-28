/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:55:59 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:12:19 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	found_old_pwd_env_and_modif(t_envp *enviroment, char *old_pwd)
{
	char	*name_variable;
	t_envp	*tmp;

	tmp = enviroment;
	name_variable = ft_strjoin("=", old_pwd);
	if (!name_variable || garbagge(ADD, name_variable, ENV))
		return ((void)0);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
			break ;
		if (!tmp->next)
		{
			tmp->next = old_nev_add_back(old_pwd, name_variable);
			return ;
		}
		tmp = tmp->next;
	}
	enviroment->value = ft_strdup(old_pwd);
	if (!enviroment->value || garbagge(ADD, enviroment->value, ENV))
		return (printf("ft_strdup FAIL\n"), (void)0);
	enviroment->path = ft_strjoin(enviroment->name, name_variable);
	if (!enviroment->path || garbagge(ADD, enviroment->path, ENV))
		return (garbagge(FREE, name_variable, ENV), garbagge(FREE,
				enviroment->value, ENV), (void)0);
}



void	found_old_pwd_exp_and_modif(t_exp *export, char *old_pwd)
{
	char	*old_modif;
	t_exp	*tmp;

	tmp = export;
	old_modif = ft_strjoin(old_pwd, "\"");
	if (!old_modif || garbagge(ADD, old_modif, ENV))
		return ((void)0);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->path, "export OLDPWD",
				ft_strlen("export OLDPWD")) == 0)
			break ;
		if (!tmp->next)
		{
			tmp->next = old_exp_add_back(old_modif);
			return ;
		}
		tmp = tmp->next;
	}
	export->value = ft_strjoin("=\"", old_modif);
	if (!export->value || garbagge(ADD, export->value, ENV))
		return (garbagge(FREE, old_modif, ENV), (void)0);
	export->path = ft_strjoin("export OLDPWD", export->value);
	if (!export->path || garbagge(ADD, export->path, ENV))
		return (garbagge(FREE, export->value, ENV), (void)0);
}

void	change_env_export_old_pwd(t_envp *enviroment, t_exp *export,
		char *old_pwd)
{
	if (!enviroment || !export)
		return (ft_putstr_fd("env ou EXPO not\n", 2), (void)0);
	found_old_pwd_env_and_modif(enviroment, old_pwd);
	found_old_pwd_exp_and_modif(export, old_pwd);
	garbagge(FREE, old_pwd, ENV);
}

void	found_cd_home(t_exp *export, t_envp *enviroment, char *home, char *pwd)
{

	if ( home && chdir(home) == 0)
	{
		change_env_export_pwd(enviroment, export, home);
		change_env_export_old_pwd(enviroment, export, pwd);
	}
	else if (home)
		ft_putstr_fd("FAIL chdir home path not found\n", 2);
}

void	change_env_export_pwd(t_envp *enviroment, t_exp *export, char *new_pwd)
{
	if (!enviroment || !export)
		return (ft_putstr_fd("env ou EXPO\n", 2), garbagge(FLUSH, NULL, ALL),
			exit(EXIT_FAILURE), (void)0);
	found_pwd_in_env_modif(enviroment, new_pwd);
	while (export)
	{
		if (ft_strncmp(export->path, "export PWD",
				ft_strlen("export PWD")) == 0)
			break ;
		export = export->next;
	}
	if (!new_pwd || !export)
		return ((void)0);
	enviroment->value = ft_strjoin(new_pwd, "\"");
	if (!export->value || garbagge(ADD, enviroment->value, ENV))
		return ((void)0);
	export->value = ft_strjoin("=\"", enviroment->value);
	if (!export->value || garbagge(ADD, export->value, ENV))
		return (garbagge(FREE, enviroment->value, ENV), (void)0);
	export->path = ft_strjoin("export PWD", export->value);
	if (!export->path || garbagge(ADD, export->path, ENV))
		return (garbagge(FREE, enviroment->value, ENV), garbagge(FREE,
				export->value, ENV), (void)0);
}
