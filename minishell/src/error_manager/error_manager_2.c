/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:23:17 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/03 15:51:33 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_error_space_replace(char *s)
{
	int	inside;
	int	i;

	i = 0;
	inside = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == '\"')
			inside = !inside;
		else if (s[i] == ' ' && !inside)
			s[i] = '\v';
		i++;
	}
	return (0);
}

int	check_if_only_space(char *s)
{
	int		i;
	char	*s2;

	s2 = s;
	i = 0;
	while (s2[i])
	{
		if (s2[i] != ' ' && s2[i] != '\"')
			return (0);
		if (s2[i] != ' ' && s2[i] != '\'')
			return (0);
		if (s2[i] != ' ' && s2[i] != '\'')
			return (0);
		if (s2[i] != '\'' && s2[i + 1] != '\'')
			return (0);
		if (s2[i] != '\"' && s2[i + 1] != '\"')
			return (0);
		i++;
	}
	return (1);
}

int	check_forb_logic(int i, int blind, char c, char *str)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !blind && str[i++])
		{
			c = '\'';
			blind = 1;
		}
		if (str[i] == '"' && !blind && str[i++])
		{
			c = '"';
			blind = 1;
		}
		if (blind)
		{
			while (str[i] != '\0' && str[i] != c)
				i++;
			if (str[i] == c)
			{
				c = '\v';
				blind = 0;
			}
		}
		i++;
	}
	return (c);
}
