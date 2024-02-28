/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_operand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:53:13 by armeyer           #+#    #+#             */
/*   Updated: 2024/02/26 14:55:01 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_found_word(char *str, int i, int where)
{
	if (where == 1)
	{
		while (i > 0)
		{
			if (ft_isalpha(str[i]))
				return (1);
			i--;
		}
	}
	if (where == 2)
	{
		while (str[i] != '\0')
		{
			if (ft_isalpha(str[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_operand_without_words(char *str, int index)
{
	int	i;
	int	previous_word;
	int	next_word;

	i = 0;
	if (str[index] == '&' && (str[index - 1] == '&' || str[index + 1] == '&'))
	{
		previous_word = 0;
		next_word = 0;
		i = index;
		previous_word = ft_found_word(str, i, 1);
		next_word = ft_found_word(str, i, 2);
		if (previous_word == 0 || next_word == 0)
		{
			ft_printf("bash syntax error near unexpected token '&&'\n");
			return (2);
		}
	}
	return (0);
}

int	ft_lone_operand(char *str, int index)
{
	if (str[index] == '&' && str[index + 1] \
	&& str[index + 1] != '&' && str[index - 1] != '&')
	{
		ft_printf("bash syntax error near unexpected token '&'\n");
		return (2);
	}
	return (0);
}

int	ft_error_operand_part_2(char *str, int index)
{
	index = 0;
	while (str[index] != '\0')
	{
		if (ft_lone_operand(str, index))
			return (2);
		if (ft_operand_without_words(str, index))
			return (2);
		index++;
	}
	return (0);
}

int	ft_error_operand(char *str, char *error_message)
{
	int		index;

	index = 0;
	if (ft_count_sign(str, '&') % 2 == 1)
	{
		ft_printf("bash syntax error near unexpected token '&'\n");
		return (2);
	}
	while (str[index] != '\0')
	{
		if (str[index] == '&')
		{
			if (str[index + 1] && str[index + 1] == '&')
			{
				if (str[index + 2])
				{
					if (str[index + 2] == '&')
						ft_printf("%s\n", error_message);
					return (2);
				}
			}
		}
		index++;
	}
	return (ft_error_operand_part_2(str, index));
}
