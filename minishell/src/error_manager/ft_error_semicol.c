/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_semicol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:47:04 by armeyer           #+#    #+#             */
/*   Updated: 2024/01/23 16:02:49 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_semicol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';' && str[i + 1] && str[i + 1] == ';')
		{
			ft_printf("bash: Syntax error near unexcpected token ';;'\n");
			return (2);
		}
		if (str[i] == ';')
		{
			ft_printf("bash: Syntax error near unexcpected token ';'\n");
			return (2);
		}
		i++;
	}
	return (0);
}
