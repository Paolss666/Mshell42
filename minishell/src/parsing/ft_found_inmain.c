/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_found_inmain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:37:25 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:41:38 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*found_path_envp_list(t_envp *enviroment)
{
	char	*env_path;

	env_path = NULL;
	if (!enviroment)
		return (NULL);
	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "PATH") == 0)
		{
			env_path = ft_strdup(enviroment->path);
			if (!env_path || garbagge(ADD, env_path, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			else
				return (env_path);
		}
		enviroment = enviroment->next;
	}
	return (NULL);
}

int	found_level(t_cmd *to_pars)
{
	t_cmd	*current;

	current = to_pars;
	if (!to_pars)
		return (0);
	while (current)
	{
		if (ft_strcmp(current->cmd, "./minishell") == 0)
			return (1);
		if (ft_strcmp(current->cmd, "bash --posix") == 0)
			return (1);
		if (ft_strcmp(current->cmd, "bash") == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	logic_found_shlvl_env(t_envp *enviroment)
{
	int		n;
	char	*tmp;

	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "SHLVL") == 0)
		{
			n = ft_atoi(enviroment->value) + 1;
			enviroment->value = ft_itoa(n);
			if (!enviroment->value || garbagge(ADD, enviroment->value, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			tmp = ft_strjoin(enviroment->name, "=");
			if (!tmp || garbagge(ADD, tmp, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			enviroment->path = ft_strjoin(tmp, enviroment->value);
			if (!enviroment->path || garbagge(ADD, enviroment->path, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			garbagge(FREE, tmp, ENV);
			return ;
		}
		enviroment = enviroment->next;
	}
	return ;
}

void	logic_found_shlvl_expo(t_exp *export)
{
	while (export)
	{
		if (ft_strncmp(export->path, "export SHLVL=",
				ft_strlen("export SHLVL=")) == 0)
		{
			change_in_exp(export);
			return ;
		}
		export = export->next;
	}
}

void	found_shlv(t_envp *enviroment, t_exp *export)
{
	if (!enviroment || !export)
		return ;
	logic_found_shlvl_env(enviroment);
	logic_found_shlvl_expo(export);
	return ;
}
