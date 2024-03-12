/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_shlvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:36:48 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 00:53:08 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	err_neg_max_int(char *cmd)
{
	ft_putstr_fd("exit: \n", 2);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit(2);
}

void	logic_shlvl_exit_exp(t_exp *export)
{
	int		n;
	char	*temp;
	char	*temp1;
	char	*final;

	export->value = ft_strchr(export->path, '=') + 1;
	export->name = ft_strdup("export SHLVL=\"");
	if (!export->name || garbagge(ADD, export->name, ENV))
		return ((void)0);
	temp1 = ft_strtrim(export->value, "\"");
	if (!temp1 || garbagge(ADD, temp1, ENV))
		return (garbagge(FREE, export->name, ENV), (void)0);
	n = ft_atoi(temp1);
	temp = ft_itoa(n);
	if (!temp || garbagge(ADD, temp, ENV))
		return (garbagge(FREE, temp1, ENV),
			garbagge(FREE, export->name, ENV), (void)0);
	final = ft_strjoin(temp, "\"");
	if (!final || garbagge(ADD, final, ENV))
		return (garbagge(FREE, temp1, ENV), garbagge(FREE, export->name, ENV),
			garbagge(FREE, temp, ENV), (void)0);
	export->path = ft_strjoin(export->name, final);
	if (!export->path || garbagge(ADD, export->path, ENV))
		return (garbagge(FREE, NULL, ENV), exit(EXIT_FAILURE), (void)0);
}

void	logic_shlvl_exit_env(t_envp *enviroment)
{
	int		n;
	char	*tmp;

	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "SHLVL") == 0)
		{
			n = ft_atoi(enviroment->value);
			enviroment->value = ft_itoa(n);
			if (!enviroment->value || garbagge(ADD, enviroment->value, ENV))
				return ((void)0);
			tmp = ft_strjoin(enviroment->name, "=");
			if (!tmp || garbagge(ADD, tmp, ENV))
				return (garbagge(FREE, enviroment->value, ENV), (void)0);
			garbagge(FREE, enviroment->path, ENV);
			enviroment->path = NULL;
			enviroment->path = ft_strjoin(tmp, enviroment->value);
			if (!enviroment->path || garbagge(ADD, enviroment->path, ENV))
				return ((void)0);
			garbagge(FREE, tmp, ENV);
			return ((void)0);
		}
		enviroment = enviroment->next;
	}
	return ((void)0);
}

void	check_shlvl_expo(t_exp *export)
{
	while (export)
	{
		if (ft_strncmp(export->path, "export SHLVL=",
				ft_strlen("export SHLVL=")) == 0)
		{
			logic_shlvl_exit_exp(export);
			return ((void)0);
		}
		export = export->next;
	}
}

void	found_shlv_exit(t_envp *enviroment, t_exp *export)
{
	if (!enviroment || !export)
		return ((void)0);
	logic_shlvl_exit_env(enviroment);
	check_shlvl_expo(export);
	return ((void)0);
}
