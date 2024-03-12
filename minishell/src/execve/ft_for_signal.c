/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:22:15 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:24:11 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	postfork_ms_sig(int signal)
{
	(void)signal;
}

void	ms_signals(void)
{
	signal(SIGINT, postfork_ms_sig);
	signal(SIGQUIT, postfork_ms_sig);
}

int	len_liste_cmd(t_cmd *cmd)
{
	int	index;

	index = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		index++;
		cmd = cmd->next;
	}
	return (index + 1);
}

void	close_if_open(int fd)
{
	if (fd != -1)
		close(fd);
}