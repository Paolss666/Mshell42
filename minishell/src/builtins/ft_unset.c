/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:52:57 by npoalett          #+#    #+#             */
/*   Updated: 2024/02/22 10:41:38 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE UNSET */

int	found_unset(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "unset", ft_strlen("unset")) == 0
			&& ft_strlen("unset") == 5)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

void	found_in_env_and_delete(t_envp **enviroment, t_cmd *to_pars)
{
	t_envp	*current;
	t_envp	*prev;

	prev = NULL;
	current = NULL;
	current = *enviroment;
	while (current != NULL && (ft_strncmp(to_pars->cmd, current->path,
				ft_strlen(to_pars->cmd)) != 0))
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL)
	{
		if (prev == NULL)
			*enviroment = current->next;
		else
			prev->next = current->next;
		garbagge(FREE, current->name, ENV);
		garbagge(FREE, current->path, ENV);
		garbagge(FREE, current->value, ENV);
		garbagge(FREE,current, ENV);
		current = *enviroment;
	}
}

void	found_in_export_and_delete(t_exp **export, t_cmd *to_pars)
{
	t_exp	*current_exp;
	t_exp	*prev_exp;
	char	*cmd;

	cmd = ft_strjoin("export ", to_pars->cmd);
	if (!cmd || garbagge(ADD, cmd, ENV))
		return ((void)0);
	current_exp = *export;
	while (current_exp != NULL && (ft_strncmp(cmd, current_exp->path,
				ft_strlen(cmd))) != 0)
	{
		prev_exp = current_exp;
		current_exp = current_exp->next;
	}
	if (current_exp != NULL)
	{
		if (prev_exp == NULL)
			*export = current_exp->next;
		else
			prev_exp->next = current_exp->next;
		garbagge(FREE, current_exp->path, ENV);
		garbagge(FREE, current_exp, ENV);
		current_exp = *export;
	}
}

void	unset_delete_variable(t_cmd *to_pars, t_envp **enviroment,
								t_exp **export)
{
	t_cmd	*next;

	if (!to_pars->next)
		return (ft_putstr_fd("unset need arguments\n", 2), (void)0);
	else
		next = to_pars->next;
	while (next)
	{
		found_in_env_and_delete(enviroment, next);
		found_in_export_and_delete(export, next);
		next = next->next;
	}
}
