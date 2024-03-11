/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_non_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:26:30 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/11 22:39:19 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	non_interactive_mode(t_brain *brain, char **env)
{
	char	*line;
	int		err;

	line = get_next_line(STDIN_FILENO);
	if (!line || garbagge(ADD, line, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(0));
	line[ft_strlen(line) - 1] = '\0';
	brain->line = line;
	err = main_brain(env, brain);
	get_next_line(0);
	garbagge(FLUSH, NULL, ALL);
	exit(err);
}

void	ft_issatty(t_brain *brain, char **env)
{
	int	fd;

	if (isatty(0))
	{
		fd = open("/dev/stdin", O_RDWR);
		if (fd < 0)
			(perror("open failed"), exit(errno));
		if (dup2(fd, STDOUT_FILENO) == -1)
			(perror("dup2 failed"), close_if_open(fd), exit(errno));
		close_if_open(fd);
	}
	if (!isatty(0))
		non_interactive_mode(brain, env);
}
