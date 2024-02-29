/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:23:05 by armeyer           #+#    #+#             */
/*   Updated: 2024/02/28 19:17:11 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_single_quotes_closed(const char *str)
{
	int		count;
	int		inside_single_quotes;
	int		i;

	count = 0;
	inside_single_quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			inside_single_quotes = !inside_single_quotes;
		if (inside_single_quotes)
			count++;
		i++;
	}
	return (count % 2 == 0);
}

void	replace_spaces(char *str)
{
	int		inside_single_quotes;
	int		inside_double_quotes;
	int		i;

	inside_single_quotes = 0;
	inside_double_quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			inside_single_quotes = !inside_single_quotes;
		if (str[i] == '\'')
			inside_double_quotes = !inside_double_quotes;
		if (!inside_single_quotes && !inside_double_quotes && str[i] == ' ')
		{
			str[i] = '\v';
		}
		i++;
	}
}

void	ft_handle_quote(char *str)
{
	replace_spaces(str);
}
