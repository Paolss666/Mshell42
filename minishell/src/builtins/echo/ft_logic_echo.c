/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:52:07 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:25:45 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_alone(char *s)
{
	if (s[1] || s[1] == ' ' || s[1] == '\"' || s[1] == '$')
		return (1);
	return (0);
}

int	found_dollar_alone(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i] == ' ')
			i++;
		i++;
	}
	return (0);
}

int	is_valid_variable_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || (c == '_') || (c == '?'));
}
