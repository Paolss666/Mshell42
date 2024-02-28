/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:55:42 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:17:21 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_cd(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "cd") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "cd -") == 0)
			return (2);
		to_pars = to_pars->next;
	}
	return (0);
}

char	*found_variable_env(t_envp *enviroment, char *name_v)
{
	while (enviroment != NULL)
	{
		if (ft_strcmp(enviroment->name, name_v) == 0)
			return (enviroment->path);
		enviroment = enviroment->next;
	}
	return (NULL);
}

char	*found_variable_exp(t_exp *export, char *name_v)
{
	while (export != NULL)
	{
		if (ft_strcmp(export->name, name_v) == 0)
			return (export->path);
		export = export->next;
	}
	return (NULL);
}

t_exp	*old_exp_add_back(char *old_modif)
{
	t_exp	*new_node;

	new_node = (t_exp *)malloc(sizeof(t_exp));
	if (!new_node || garbagge(ADD, new_node, ENV))
		return (NULL);
	new_node->value = ft_strjoin("=\"", old_modif);
	if (!new_node->value || garbagge(ADD, new_node->value, ENV))
		return (garbagge(FREE, new_node->value, ENV), NULL);
	new_node->path = ft_strjoin("export OLDPWD", new_node->value);
	if (!new_node->path || garbagge(ADD, new_node->path, ENV))
		return (garbagge(FREE, new_node->value, ENV), NULL);
	new_node->name = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_envp	*old_nev_add_back(char *old_pwd, char *name_variable)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node || garbagge(ADD, new_node, ENV))
		return (NULL);
	new_node->name = ft_strdup("OLDPWD");
	if (!new_node || garbagge(ADD, new_node->name, ENV))
		return (garbagge(FLUSH, NULL, ENV), NULL);
	new_node->value = ft_strdup(old_pwd);
	if (!new_node->value || garbagge(ADD, new_node->value, ENV))
		return (garbagge(FLUSH, NULL, ENV), NULL);
	new_node->path = ft_strjoin("OLDPWD", name_variable);
	if (!new_node->path || garbagge(ADD, new_node->path, ENV))
		return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	new_node->next = NULL;
	return (new_node);
}