/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:00:48 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:38:27 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_cmd	*free_cmds_list(t_cmd *head)
{
	t_cmd	*history;

	history = head;
	if (history)
	{
		garbagge(FREE, history->cmd, PARS);
		garbagge(FREE, history, PARS);
		return (NULL);
	}
	else
		return (head);
}

t_exp	*free_exp_list(t_exp *head)
{
	t_exp	*history;

	history = head;
	if (history)
	{
		garbagge(FREE, history->path, ENV);
		garbagge(FREE, history->value, ENV);
		garbagge(FREE, history->name, ENV);
		garbagge(FREE, history, ENV);
		return (NULL);
	}
	else
		return (head);
}

void	free_cmd_list(t_cmd *head)
{
	if (head)
	{
		garbagge(FREE, head->cmd, PARS);
		garbagge(FREE, head, PARS);
	}
	return ((void)0);
}

/* --->>>>> toutes les commandes mis dans les listes chainees <<-------- */
void	ft_free_tab_garbage(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		garbagge(FREE, tab[i], PARS);
	garbagge(FREE, tab, PARS);
}
