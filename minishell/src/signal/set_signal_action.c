/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:52:06 by armeyer           #+#    #+#             */
/*   Updated: 2024/02/19 21:27:04 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

extern int	g_signal_received;


void	sigint_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		ft_putstr_fd("\n", 2);
		g_signal_received = 60;
	}
}

void	sigint_handler(int signal)
{
	extern int	g_signal_received;

	if (signal == SIGINT)
	{
		g_signal_received = 60;
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal_action(int sig_case)
{
	if (sig_case == 1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig_case == 2)
	{
		signal(SIGINT, &sigint_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig_case == 3)
	{
		g_signal_received = 60;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
