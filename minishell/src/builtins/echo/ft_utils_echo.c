/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:07 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:16:31 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*funny_commande_echo(const char *next_command)
{
	size_t	command_length;
	char	*result;

	command_length = ft_strlen(next_command);
	result = malloc(command_length + 1);
	if (garbagge(ADD, result, PARS))
		return ((garbagge(FLUSH, NULL, ALL), exit(99)), NULL);
	if (result != NULL)
	{
		ft_strcpy(result, next_command, ft_strlen(next_command));
		return (result);
	}
	return (NULL);
}

char	*get_first_non_n_token(const char *cmd)
{
	const char	*token;
	const char	*delimiter;
	const char	*next_command;
	const char	*first_delimiter;
	const char	*next_command_start;

	token = "echo -n";
	delimiter = " ";
	next_command_start = ft_strstr(cmd, token) + ft_strlen(token);
	if (next_command_start == NULL)
		return (NULL);
	first_delimiter = ft_strchr(next_command_start, delimiter[0]);
	if (first_delimiter == NULL)
		return (NULL);
	next_command = first_delimiter;
	while (*next_command == ' ')
		next_command++;
	if (ft_strncmp(next_command, "-n", 2) != 0)
		return (funny_commande_echo(next_command));
	return (NULL);
}

int	ft_check_flag(char *flag, int i, int j)
{
	while (flag[i])
	{
		if (flag[i] != 'n' && flag[i] != '\0')
		{
			if (flag[i] == ' ' && flag[i + 1]
				&& flag[i + 1] == '-' && flag[i + 2])
			{
				j = i + 1;
				return (ft_check_flag(flag, i + 2, j));
			}
			if (j == 0)
				return (-2);
			return (j);
		}
		i++;
	}
	return (-1);
}

int	process_echo_dash(t_cmd *to_pars, char *tmp)
{
	char	*vl;
	int		j;

	vl = ft_substr(tmp, 5, ft_strlen(tmp));
	if (!vl || garbagge(ADD, vl, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	remove_q(vl);
	j = ft_check_flag(vl + 1, 0, 0);
	if (j > -1)
	{
		if (j > -1)
			printf("%s ", vl + j + 1);
		to_pars->cmd = NULL;
		to_pars->cmd = ft_strdup("echo -n");
	}
	else
	{
		printf("%s ", vl);
		to_pars->cmd = NULL;
		to_pars->cmd = ft_strdup("echo");
	}
	if (!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	return (-1);
}

int	found_with_check_flag(t_cmd *to_pars, char *tmp)
{
	if (ft_check_flag(tmp + 6, 0, 0) == -1)
	{
		to_pars->cmd = ft_strdup("echo -n");
		if (!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
			(garbagge(FLUSH, NULL, ALL), exit(99));
		return (garbagge(FREE, tmp, PARS), 2);
	}
	return (0);
}
