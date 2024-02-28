/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_stx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:02:53 by armeyer           #+#    #+#             */
/*   Updated: 2024/01/23 16:05:45 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_stx(char *str)
{
	int		i;
	char	c;
	char	d;

	i = 0;
	c = '"';
	d = 39;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			printf("bash: Syntax error near unexcpected token %c\n", c);
			return (2);
		}
		if (str[i] == 39)
		{
			printf("bash: Syntax error near unexcpected token %c\n", d);
			return (2);
		}
		i++;
	}
	return (0);
}
