/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:23:17 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/05 12:29:43 by npaolett         ###   ########.fr       */
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

int    check_forb_logic(int i, char c, char *str)
{
    while (str[i] != '\0')
    {
        if (str[i] == '\'' && c == '\v')
            c = '\'';
        else
        {
            if (str[i] == '"' && c == '\v')
                c = '"';
        }
        if (c != '\v' && str[i + 1])
        {
            i++;
            while (str[i] != '\0' && str[i] != c)
                i++;
            if (str[i] == c)
                c = '\v';
        }
        i++;
    }
    return (c);
}
