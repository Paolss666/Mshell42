/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_shift_operator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:03:04 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/03 16:06:06 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* int	no_words_before(char *str, int indice)
{
	if (indice == 0)
		return (0);
	indice--;
	while (indice != -1)
	{
		if (str[indice] != '<' && str[indice] != '>' && \
		str[indice] != ' ' && str[indice] != '\v')
			return (0);
		indice--;
	}
	return (1);
} */

int	no_words_after(char *str, int indice)
{
	if (indice == 0)
		return (0);
	indice++;
	while (str[indice] != '\0')
	{
		if (str[indice] != '<' && str[indice] != '>' && \
		str[indice] != '\v' && str[indice] != ' ')
			return (0);
		indice++;
	}
	return (1);
}

int	ft_error_shift_operator_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (no_words_after(str, i))
			{
				printf("bash: syntax error near unexpected token\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_error_shift_operator(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '\t' || str[i] == ' ')
			count++;
		i++;
	}
	if (!count)
		return (0);
	if (ft_strlen(str) == 2)
	{
		ft_printf("bash: syntax error near unexpected token 'newline'\n");
		return (2);
	}
	if (ft_error_shift_operator_2(str))
		return (2);
	return (0);
}
