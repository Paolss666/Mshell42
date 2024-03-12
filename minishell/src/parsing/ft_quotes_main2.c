/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_main2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:09:14 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 03:13:38 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	count_quotes_f_spl(const char *str)
{
	int		count;
	char	quote;

	count = 0;
	quote = '\0';
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == '\0')
				quote = *str;
			else if (*str == quote)
			{
				quote = '\0';
				count++;
			}
		}
		str++;
	}
	return (count);
}

char	*replace_v(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			s[i] = '\v';
		i++;
	}
	return (s);
}