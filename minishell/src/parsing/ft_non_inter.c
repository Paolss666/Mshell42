/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_non_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:26:30 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/05 21:46:00 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	non_interactive_mode(t_brain *brain)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (!line || garbagge(ADD, line, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(0));
	line[ft_strlen(line) - 1] = '\0';
	brain->line = line;
	(get_next_line(0), garbagge(FLUSH, NULL, ALL), exit(1));
}

void	ft_issatty(t_brain *brain)
{
	int		fd;
	
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
		non_interactive_mode(brain);
}
