/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:47 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/08 12:11:51 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	found_cd_et_pass(t_cmd *to_pars, t_envp *enviroment, t_exp *export,
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
			return (ft_putstr_fd(to_pars->next->cmd, 2), perror(" "), 1);
		change_env_export_pwd(enviroment, export, pwd);
	}
	else
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(to_pars->next->cmd, 2);
		ft_putstr_fd(" : not such a file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	print_old_and_go(t_l_cd *cd, t_envp *enviroment, t_exp *export)
{
	char	*line;

	line = NULL;
	cd->old_pwd = cd->pwd;
	change_env_export_old_pwd(enviroment, export, cd->old_pwd);
	cd->pwd = getcwd(NULL, 0);
	if (!cd->pwd || garbagge(ADD, cd->pwd, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	change_env_export_pwd(enviroment, export, cd->pwd);
	line = ft_substr(cd->pwd, ft_strlen(cd->home), ft_strlen(cd->pwd));
	if (!line || garbagge(ADD, line, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	line = ft_strjoin("~", line);
	if (!line || garbagge(ADD, line, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	printf("%s\n", line);
}

int	found_cd_oldpwd(t_exp *export, t_envp *enviroment, t_l_cd *cd)
{
	cd->pwd = getcwd(NULL, 0);
	if (!cd->pwd || garbagge(ADD, cd->pwd, ENV) || !cd->home)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd("cd :", 2);
		ft_putstr_fd("OLDPWD not set\n", 2);
		return (1);
	}
	if (cd->old_pwd && chdir(cd->old_pwd) == 0)
		print_old_and_go(cd, enviroment, export);
	else
	{
		cd->old_pwd = old_pwd_not_found(cd->pwd, enviroment, export);
		return (2);
	}
	return (0);
}


int		logic_cd(t_cmd *to_pars, t_exp *export, t_envp *enviroment, t_l_cd *cd)
{
	int	err;

	err = 0;
	if (cd->home)
		cd->home = home_found(cd->home);
	if (ft_cd(to_pars) == 1 && !to_pars->next && cd->home)
		err = found_cd_home(export, enviroment, cd->home, cd->pwd);
	else if (ft_cd(to_pars) == 1 && !to_pars->next && !cd->home)
		err = ft_home_not_found(cd->home);
	if (ft_cd(to_pars) && to_pars->next && !to_pars->next->next)
		err = found_cd_et_pass(to_pars, enviroment, export, cd->pwd);
	if (ft_cd(to_pars) == 2 && !to_pars->next)
		err = found_cd_oldpwd(export, enviroment, cd);
	return (err);
}

int	found_cd_pwd_update(t_cmd *to_pars, t_envp *enviroment, t_exp *export)
{
	t_l_cd	*cd;
	int		err;

	err = 0;
	cd = (t_l_cd *)malloc(sizeof(t_l_cd));
	if (!cd || garbagge(ADD, cd, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	cd->pwd = getcwd(NULL, 0);
	if (garbagge(ADD, cd->pwd, ENV))
		return (3);
	cd->home = found_variable_env(enviroment, "HOME");
	cd->old_pwd = found_variable_env(enviroment, "OLDPWD");
	if (cd->old_pwd)
	{
		cd->old_pwd = ft_substr(cd->old_pwd, ft_strlen("OLDPWD="),
				ft_strlen(cd->old_pwd));
		if (garbagge(ADD, cd->old_pwd, ENV))
			return (3);
	}
	err = logic_cd(to_pars, export, enviroment, cd);
	return (err);
}
