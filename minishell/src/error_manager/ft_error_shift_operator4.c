/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_shift_operator4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:41:27 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/07 13:02:31 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	contradicting_redir(char *str)
{
	int		i;
	int		index;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] && (str[i] == '>' || str[i] == '<'))
		{
			c = str[i];
			i++;
			index = i;
			while (str[i + 1]
				&& (str[i] == ' ' || str[i] == '\v' || str[i] == '\t'))
				i++;
			if (index != i && (str[i] == '<' || str[i] == '>'))
			{
				c = str[i];
				printf("bash: syntax error near unexpected token '%c'\n", c);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	redir_space_redir(char *str)
{
	int		i;
	int		indice;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			c = str[i];
			indice = i;
			while (str[i] == '\v' || str[i] == ' ' || str[i] == '\t')
				i++;
			if ((str[i] == '<' || str[i] == '>') && i != indice)
			{
				printf("bash: syntax error near unexpected token '%c'\n", c);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	special_redir_case(char *str)
{
	if (ft_strnstr(str, "<<>>", ft_strlen(str)) != NULL)
	{
		printf("bash: syntax error near unexpected token '>>'\n");
		return (1);
	}
	if (ft_strnstr(str, ">><<", ft_strlen(str)) != NULL)
	{
		printf("bash: syntax error near unexpected token '<<'\n");
		return (1);
	}
	if (ft_strnstr(str, "><", ft_strlen(str)) != NULL)
	{
		printf("bash: syntax error near unexpected token '<'\n");
		return (1);
	}
	if (ft_strnstr(str, ">>|<<", ft_strlen(str)) != NULL)
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (1);
	}
	if (redir_space_redir(str))
		return (1);
	return (0);
}
