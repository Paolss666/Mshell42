/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_case_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:52 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/01 15:28:12 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_case_1_part_3(char c)
{
	if (c == '.')
	{
		ft_printf("bash: .: filename argument required\n");
		return (2);
	}
	if (c == '$')
	{
		ft_printf("bash: $: command not found\n");
		return (127);
	}
	if (c == '|')
	{
		ft_printf("bash: syntax error near unexpected token '|'\n");
		return (2);
	}
	return (0);
}

int	ft_error_case_1_part_2(char c)
{
	if (c == '-')
	{
		ft_printf("bash: -: command not found\n");
		return (127);
	}
	if (c == '\v')
	{
		ft_printf("bash: crashtest.c: command not found\n");
		return (127);
	}
	return (ft_error_case_1_part_3(c));
}

int	ft_error_case_1(char c)
{
	int	error_status;

	if (c == '\t' || c == ':' || c == '!' || c == '#')
	{
		if (c == '\t' || c == ':' || c == '#')
			return (999);
		if (c == '!')
			return (1);
	}
	if (c == '<' || c == '>')
	{
		ft_printf("bash: syntax error near unexpected token 'newline'\n");
		return (2);
	}
	error_status = ft_error_case_1_part_2(c);
	if (error_status)
		return (error_status);
	return (0);
}
