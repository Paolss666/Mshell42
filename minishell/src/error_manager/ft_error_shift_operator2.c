/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_shift_operator2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:05:59 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/06 14:09:34 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_multiples_left(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
		{
			while (str[i] != '\0' && str[i] == '<')
			{
				count++;
				i++;
			}
			if (count == 5)
			{
				printf("bash: syntax error near unexpected token '<<'\n");
				return (1);
			}
			count = 0;
		}
		i++;
	}
	return (0);
}

int	check_multiple_left(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
		{
			while (str[i] != '\0' && str[i] == '<')
			{
				count++;
				i++;
			}
			if (count == 4)
			{
				printf("bash: syntax error near unexpected token '<'\n");
				return (1);
			}
			count = 0;
		}
		i++;
	}
	return (0);
}

int	check_multiples_right(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
		{
			while (str[i] != '\0' && str[i] == '>')
			{
				count++;
				i++;
			}
			if (count > 3)
			{
				printf("bash: syntax error near unexpected token '>>'\n");
				return (1);
			}
			count = 0;
		}
		i++;
	}
	return (0);
}

int	check_multiple_right(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
		{
			while (str[i] != '\0' && str[i] == '>')
			{
				count++;
				i++;
			}
			if (count == 3)
			{
				printf("bash: syntax error near unexpected token '>'\n");
				return (1);
			}
			count = 0;
		}
		i++;
	}
	return (0);
}

int	ft_check_multiple_operator(char *str)
{
	if (check_multiple_right(str))
		return (1);
	if (check_multiples_right(str))
		return (1);
	if (check_multiple_left(str))
		return (1);
	if (check_multiples_left(str))
		return (1);
	if (check_multipless_left(str))
		return (1);
	return (0);
}
