/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:49:58 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:52:45 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	replace_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			str[i] = '\v';
		}
		i++;
	}
}

int	contains_only_spaces(const char *str)
{
	if (*str == ' ' && *(str + 1) == '\0')
		return (0);
	while (*str != '\0')
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	count_single_quotes(char *cmd)
{
	int	c;
	int	i;

	c = 0;
	i = -1;
	while (cmd[++i])
		if (cmd[i] == '\'')
			c++;
	if (c == 0)
		return (1);
	else if (c % 2 == 0)
		return (0);
	return (1);
}

int	has_both_quotes(const char *str)
{
	int	sngl;
	int	db;
	int	i;

	sngl = 0;
	db = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sngl = 1;
		else if (str[i] == '"')
			db = 1;
		if (sngl && db)
			return (1);
		i++;
	}
	return (0);
}

int	logic_check_type_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (has_both_quotes(str))
			return (4);
		if ((str[i] == '\'' && (str[i + 1] == '\v' || str[i + 1] == '\0'
				|| is_valid_variable_char(str[i + 1]))))
			return (2);
		if (str[i] == '\"' && (str[i + 1] == '\v' || str[i + 1] == '\0'))
			return (3);
		i++;
	}
	return (0);
}