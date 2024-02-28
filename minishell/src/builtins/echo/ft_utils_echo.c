/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:07 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 15:03:25 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	found_echo(t_cmd *to_pars)
{
	char	*ptr;

	ptr = NULL;
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "echo") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "echo -n") == 0)
			return (2);
		if (ft_strncmp(to_pars->cmd, "echo -n", 7) == 0 && !to_pars->next)
		{
			ptr = to_pars->cmd + 6;
			while (*ptr)
			{
				if (*ptr != 'n')
					return (perror(" "), 0);
				ptr++;
			}
			return (2);
		}
		to_pars = to_pars->next;
	}
	return (0);
}

int	valid_variable_char(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

char	*logic_f_dollar_int(char *current, int error_status)
{
	if (ft_strcmp(current, "?") == 0)
	{
		current = ft_itoa(error_status);
		if (!current || garbagge(ADD, current, PARS))
			return (NULL);
		return (current);
	}
	return (NULL);
}

int	is_special_char(char c)
{
	char	*special_chars;
	int		i;

	special_chars = "-[]=}{:/.+@#!?~^'\" ";
	i = 0;
	while (special_chars[i])
	{
		if (c == special_chars[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_dollar(char *string)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (string[++i])
		if (string[i] == '$')
			c++;
	return (c);
}

