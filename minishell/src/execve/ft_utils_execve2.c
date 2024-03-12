/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_execve2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 01:03:30 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 01:06:24 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_file_list_array_size(t_file ***file)
{
	int	size;

	size = 0;
	while (file[size] != NULL)
		size++;
	return (size);
}

char	*change_in_quotes_espace(char *cmd, char replacement)
{
	int	i;
	int	inside_quotes;

	i = 0;
	inside_quotes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			inside_quotes = !inside_quotes;
		else if (inside_quotes && cmd[i] == '*')
			cmd[i] = replacement;
		i++;
	}
	return (cmd);
}

void	close_if_plus_zero(t_execve *pipex)
{
	close(pipex->tmp_fd[pipex->current_pipe][0]);
	close(pipex->tmp_fd[pipex->current_pipe][1]);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	if_not_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (ft_isalpha(s[i]) || s[i] == '-')
			return (0);
		i++;
	}
	return (i);
}

int	ft_check_valid_flag_echo(char *s)
{
	int	i;

	i = 0;
	if (s && s[i] == '-' && s[i + 1])
	{
		while (s[++i])
		{
			if (s[i] != 'n')
				return (1);
		}
		return (0);
	}
	return (1);
}
