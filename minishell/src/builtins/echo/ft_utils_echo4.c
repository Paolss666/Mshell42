/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:13:46 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:29:22 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	found_echo(t_cmd *to_pars)
{
	char	*tmp;

	tmp = ft_strdup(to_pars->cmd);
	if (!tmp || garbagge(ADD, tmp, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	remove_q(tmp);
	if (ft_strcmp(tmp, "echo") == 0)
	{
		to_pars->cmd = ft_strdup("echo");
		if (!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
			(garbagge(FLUSH, NULL, ALL), exit(99));
		return (garbagge(FREE, tmp, PARS), 1);
	}
	if (ft_strncmp(tmp, "echo -n", ft_strlen("echo -n")) == 0)
		if (found_with_check_flag(to_pars, tmp))
			return (garbagge(FREE, tmp, PARS), 2);
	if (ft_strncmp(tmp, "echo -", 6) == 0)
	{
		process_echo_dash(to_pars, tmp);
		return (garbagge(FREE, tmp, PARS), 1);
		garbagge(FREE, tmp, PARS);
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
