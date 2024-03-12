/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:54:59 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 02:36:49 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	found_token(t_cmd *to_pars)
{
	while (to_pars)
	{
		if (ft_strcmp(to_pars->cmd, "export") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "unset") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "echo") == 0)
			return (1);
		if (ft_strncmp(to_pars->cmd, "echo -", 6) == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "env") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "cd") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "cd -") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "exit") == 0)
			return (1);
		if (ft_strncmp(to_pars->cmd, "exit -", ft_strlen("exit -")) == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "pwd") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

int	len_liste_exp(t_exp *enviromet)
{
	int	index;

	index = 0;
	if (!enviromet)
		return (0);
	while (enviromet)
	{
		index++;
		enviromet = enviromet->next;
	}
	return (index + 1);
}

int	len_liste_envp(t_envp *enviromet)
{
	int	index;

	index = 0;
	if (!enviromet)
		return (0);
	while (enviromet)
	{
		index++;
		enviromet = enviromet->next;
	}
	return (index + 1);
}

char	*init_for_join_found_flag(t_cmd *next, t_cmd *current)
{
	char	*espace;
	char	*temp_cmd;

	espace = ft_strjoin(" ", next->cmd);
	if (!espace || garbagge(ADD, espace, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	temp_cmd = ft_strjoin(current->cmd, espace);
	if (!temp_cmd || garbagge(ADD, temp_cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	return (temp_cmd);
}

int	join_found_flag(t_cmd **to_pars)
{
	t_cmd	*current;
	t_cmd	*next;
	int		count;

	next = NULL;
	count = 0;
	current = *to_pars;
	if (!*to_pars)
		return (0);
	while (current != NULL && current->cmd != NULL)
	{
		next = current->next;
		while (next != NULL && next->cmd != NULL && next->cmd[0] == '-')
		{
			current->cmd = init_for_join_found_flag(next, current);
			current->next = next->next;
			next = current->next;
		}
		count++;
		current = current->next;
	}
	return (count);
}
