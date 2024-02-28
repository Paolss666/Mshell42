/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:10:10 by armeyer           #+#    #+#             */
/*   Updated: 2024/02/26 15:06:08 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_pipe_syntax_2(char *str, int i, int j)
{
	while (j < i)
	{
		if (str[i] != '|' && str[i] != '\v' && str[i] != ' ')
			return (1);
		j++;
	}
	j++;
	while (str[j] != '\0')
	{
		if (str[i] != '|' && str[i] != '\v' && str[i] != ' ')
			return (1);
		j++;
	}
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t')
		i--;
	if (str[i] == '|')
		return (2);
	return (0);
}

int	ft_error_pipe_syntax(char *str, int i, int j)
{
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				printf("bash syntax error near unexpected token '||'\n");
				return (2);
			}
			j = 0;
			if (ft_error_pipe_syntax_2(str, i, j))
			{
				printf("bash syntax error near unexpected token '|'\n");
				return (2);
			}
		}
		i++;
	}
	return (0);
}

int	ft_error_pipe_no_word_2(char *str, int i, int count)
{
	if (str[i] == '\0')
	{
		printf("bash syntax error near unexpected token '|'\n");
		return (2);
	}
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '|' && str[i] != '\v' && str[i] != ' ')
			count++;
		i++;
	}
	if (count == 0)
	{
		ft_printf("bash syntax error near unexpected token '|'\n");
		return (2);
	}
	return (0);
}

int	ft_error_pipe_no_word(char *str, int i, int count)
{
	if (count == 1)
	{
		i = 0;
		count = 0;
		while (str[i] != '|')
		{
			if (str[i] != '|' && str[i] != '\v' && str[i] != ' ')
				count++;
			i++;
		}
		if (count == 0)
		{
			printf("bash syntax error near unexpected token '|'\n");
			return (2);
		}
		i++;
		if (ft_error_pipe_no_word_2(str, i, count))
			return (2);
	}
	return (ft_only_pipe(str));
}

int	ft_error_pipe(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	if (count == 0)
		return (0);
	i = 0;
	if (ft_error_pipe_no_word(str, i, count))
		return (2);
	if (ft_error_pipe_syntax(str, i, j))
		return (2);
	if (ft_error_pipe_in_pipe(str))
		return (2);
	return (0);
}
