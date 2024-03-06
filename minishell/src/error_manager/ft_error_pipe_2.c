/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_pipe_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:04:45 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/06 13:30:32 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_redir_before_pipe(char *str)
{
	int	i;
	int	index;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			index = i + 1;
			i--;
			while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
				i--;
			if (str[i] == '>' || str[i] == '<')
			{
				printf("bash syntax error near unexpected token '|'\n");
				return (1);
			}
			i = index;
		}
		i++;
	}
	return (0);
}

int	ft_only_pipe(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '|' && str[i] != ' ' && str[i] != '\t' && str[i] != '\v')
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (0);
	printf("bash syntax error near unexpected token '|'\n");
	return (2);
}

int	ft_error_pipe_in_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t')
				i++;
			if (str[i] == '|')
			{
				ft_printf("bash syntax error near unexpected token '|'\n");
				return (2);
			}
		}
		i++;
	}
	return (0);
}
