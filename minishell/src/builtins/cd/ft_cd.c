/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:47 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/02 18:24:41 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

t_cd	*cpy_cd_list(char **splits, t_cd *commande_cd)
{
	t_cd	*current;
	t_cd	*envp;
	int		i;

	i = -1;
	while (splits[++i])
	{
		current = (t_cd *)malloc(sizeof(t_cmd));
		if (!current || garbagge(ADD, current, PARS))
			return (perror("FAIL malloc t_cd"), NULL);
		current->path = ft_strdup(splits[i]);
		if (!current->path || garbagge(ADD, current->path, PARS))
			return (garbagge(FREE, current, PARS), NULL);
		current->next = NULL;
		if (!commande_cd)
			commande_cd = current;
		else
		{
			envp = commande_cd;
			while (envp->next != NULL)
				envp = envp->next;
			envp->next = current;
		}
	}
	return (commande_cd);
}

void	found_cd_et_pass(t_cmd *to_pars, t_envp *enviroment, t_exp *export,
		char *pwd)
{
	char	*old_pwd;

	old_pwd = NULL;
	if (chdir(to_pars->next->cmd) == 0)
	{
		if (pwd)
			old_pwd = pwd;
		change_env_export_old_pwd(enviroment, export, old_pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd || garbagge(ADD, pwd, ENV))
			return (ft_putstr_fd(to_pars->next->cmd, 2), perror(" "), (void)0);
		change_env_export_pwd(enviroment, export, pwd);
	}
	else
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(to_pars->next->cmd, 2);
		ft_putstr_fd(" : is not a directory\n", 2);
	}
}

void	found_cd_oldpwd(t_exp *export, t_envp *enviroment, char *old_pwd,
		char *home)
{
	char	*line;
	char	*pwd;

	line = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd || garbagge(ADD, pwd, ENV) || !home)
		return (perror(" "), (void)0);
	if (old_pwd && chdir(old_pwd) == 0)
	{
		old_pwd = pwd;
		change_env_export_old_pwd(enviroment, export, old_pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd || garbagge(ADD, pwd, ENV))
			return ((void)0);
		change_env_export_pwd(enviroment, export, pwd);
		line = ft_substr(pwd, ft_strlen(home), ft_strlen(pwd));
		if (!line || garbagge(ADD, line, ENV))
			return (perror("FAIL ft_substr cd"), (void)0);
		line = ft_strjoin("~", line);
		if (!line || garbagge(ADD, line, ENV))
			return ((void)0);
		printf("%s\n", line);
	}
	else
		old_pwd = old_pwd_not_found(pwd, enviroment, export);
}

/* JE DOIT IMPLEMENTER D'ABORD LE PIPE E LE ex */
void	found_cd_pwd_update(t_cmd *to_pars, t_envp *enviroment, t_exp *export)
{
	char	*pwd;
	char	*home;
	char	*old_pwd;

	pwd = getcwd(NULL, 0);
	if (garbagge(ADD, pwd, ENV))
		return ((void)0);
	home = found_variable_env(enviroment, "HOME");
	old_pwd = found_variable_env(enviroment, "OLDPWD");
	if (old_pwd)
	{
		old_pwd = ft_substr(old_pwd, ft_strlen("OLDPWD="), ft_strlen(old_pwd));
		if (garbagge(ADD, old_pwd, ENV))
			return ((void)0);
	}
	if (home)
		home = home_found(home);
	if (ft_cd(to_pars) == 1 && !to_pars->next && home)
		found_cd_home(export, enviroment, home, pwd);
	else if (ft_cd(to_pars) == 1 && !to_pars->next && !home)
		ft_home_not_found(home);
	if (ft_cd(to_pars) && to_pars->next && !to_pars->next->next)
		found_cd_et_pass(to_pars, enviroment, export, pwd);
	if (ft_cd(to_pars) == 2 && !to_pars->next)
		found_cd_oldpwd(export, enviroment, old_pwd, home);
}
