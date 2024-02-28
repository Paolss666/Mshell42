/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:53:44 by armeyer           #+#    #+#             */
/*   Updated: 2024/02/28 11:57:58 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	count_quote(char *str, char c, char d)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c || str[i] == d)
			count++;
		i++;
	}
	return (count);
}

int	kill_double_quote(char *str, int i, int j, int flag)
{
	int	index;

	while (str[i])
	{
		if (str[i] == '\"')
			flag = 1;
		if (str[i + 1] == '\"' && flag == 1)
		{
			j = i + 2;
			index = i;
			while (str[j] != '\0')
			{
				str[i] = str[j];
				i++;
				j++;
			}
			str[i] = '\0';
			i = index;
		}
		flag = 0;
		i++;
	}
	return (0);
}

void	kill_single_quote(char *str, int i, int j, int flag)
{
	int	index;

	while (str[i])
	{
		if (str[i] == '\'')
			flag = 1;
		if (str[i + 1] == '\'' && flag == 1)
		{
			j = i + 2;
			index = i;
			while (str[j] != '\0')
			{
				str[i] = str[j];
				i++;
				j++;
			}
			str[i] = '\0';
			i = index;
		}
		flag = 0;
		i++;
	}
}

int	kill_useless_quote(char *str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	kill_single_quote(str, i, j, flag);
	kill_double_quote(str, i, j, flag);
	return (0);
}
