/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parenthesis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:01 by armeyer           #+#    #+#             */
/*   Updated: 2024/01/24 16:44:42 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_parenthesis(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ')')
		{
			ft_printf("bash: Syntax error near unexcpected token ')'\n");
			return (2);
		}
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			ft_printf("bash: Syntax error near unexcpected token '('\n");
			return (2);
		}
		i++;
	}
	return (0);
}
