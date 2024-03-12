/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_goodpth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:58:00 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 03:01:13 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_good_path_access(t_cmd *to_pars, t_envp *enviroment,
		t_execve *pipex)
{
	char	**env_split;
	char	**with_flag;
	char	*found_in_env;
	char	*tmp;

	tmp = ft_strdup(to_pars->cmd);
	if (!tmp || garbagge(ADD, tmp, PARS))
		return (NULL);
	found_in_env = NULL;
	env_split = NULL;
	with_flag = ft_split_garbage_gogo(to_pars->cmd, ' ');
	if (!with_flag || !with_flag[0] || with_flag[0][0] == '\0')
		return (NULL);
	if ((tmp[0] == '\'' && ft_strlen(tmp) == 1) || (tmp[0] == '\"'
			&& ft_strlen(tmp) == 1))
		return (NULL);
	found_in_env = found_path_envp_list(enviroment);
	if (!found_in_env)
		return (NULL);
	env_split = ft_split_garbage(found_in_env + 5, ':');
	if (!env_split)
		return (ft_free_tab_garbage(with_flag), NULL);
	if (with_flag[0])
		return (logic_get_good_path(with_flag, env_split, pipex));
	return (NULL);
}

char	**envp_list_to_new_env(t_envp *enviroment)
{
	char	**new_enviroment;
	int		i;

	i = 0;
	new_enviroment = (char **)malloc(sizeof(char *) * len_liste_envp(enviroment)
			+ 1);
	if (!new_enviroment || garbagge(ADD, new_enviroment, ENV))
		return (NULL);
	if (!enviroment || len_liste_envp(enviroment) <= 0)
		return (NULL);
	while (enviroment)
	{
		new_enviroment[i] = ft_strdup(enviroment->path);
		if (!new_enviroment[i] || garbagge(ADD, new_enviroment[i], ENV))
			return (ft_free_tab_garbage(new_enviroment), NULL);
		enviroment = enviroment->next;
		i++;
	}
	new_enviroment[i] = NULL;
	return (new_enviroment);
}

void	logic_expand_variable(int i, t_envp *enviroment, t_cmd *current,
		int e_st)
{
	char	*new_cmd;

	new_cmd = logic_print_variable(i, enviroment, current, e_st);
	if (new_cmd)
	{
		if (ft_strcmp(new_cmd, " ") == 0)
			new_cmd = NULL;
		else
		{
			if (new_cmd)
			{
				current->cmd = ft_strdup(new_cmd);
				if (!current->cmd || garbagge(ADD, current->cmd, PARS))
					return ((void)0);
				garbagge(FREE, new_cmd, PARS);
			}
			garbagge(FREE, new_cmd, PARS);
		}
	}
	new_cmd = NULL;
}

int	logic_found_dollar_interrogation(t_cmd *current, int error_status)
{
	if (ft_strcmp(current->cmd, "$?") == 0 && !current->next)
	{
		garbagge(FREE, current->cmd, PARS);
		current->cmd = ft_itoa(error_status);
		if (!current->cmd || garbagge(ADD, current->cmd, PARS))
			return (1);
		return (1);
	}
	return (0);
}

t_cmd	*expand_dollar(t_cmd **to_pars, t_envp *environment, int error_status)
{
	int		i;
	t_cmd	*current;
	t_cmd	*prev;

	i = 1;
	prev = NULL;
	current = *to_pars;
	if (!environment)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(current->cmd, "$") == 0 && current->next)
			current = current->next;
		if (ft_strcmp(current->cmd, "$?") == 0 && current->next)
		{
			current->cmd = ft_itoa(error_status);
			if (!current->cmd || garbagge(ADD, current->cmd, PARS))
				return (NULL);
		}
		if (!prev || (prev && ft_strcmp(prev->cmd, "<<")))
			logic_exp_quotes(error_status, i, environment, current);
		prev = current;
		current = current->next;
	}
	return (*to_pars);
}
