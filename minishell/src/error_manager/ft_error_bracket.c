/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bracket.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:13:47 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/07 12:50:31 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_bracket(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '}')
		{
			ft_printf("bash: Syntax error near unexcpected token '}'\n");
			return (2);
		}
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '{')
		{
			ft_printf("bash: Syntax error near unexcpected token '{'\n");
			return (2);
		}
		i++;
	}
	return (0);
}
