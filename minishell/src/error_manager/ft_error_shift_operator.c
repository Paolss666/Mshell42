/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_shift_operator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:03:04 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/06 14:16:57 by armeyer          ###   ########.fr       */
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
int	no_word(char *str, int indice)
{
	int	flag;

	flag = 1;
	indice++;
	indice++;
	if (str[indice] == '\0')
		return (flag);
	while (str[indice] != '\0')
	{
		if (str[indice] != ' ' && str[indice] != '\v' && str[indice] != '\t')
			flag = 0;
		indice++;
	}
	return (flag);
}

int	unexpected_pipe(char *str)
{
	int		i;
	char	c;

	c = '*';
	i = 0;
	while (str[i])
	{
		if (c == '*' && str[i] == '>')
		{
			if (str[i + 1] && str[i + 1] == '|')
			{
				if (no_word(str, i))
					return (1);
			}
			if (str[i + 1] && str[i + 1] == '|' && str[i + 2] && str[i + 2] == '<')
				return (2);
		}
		if (c == '*' && (str[i] == '\'' || str[i] == '\"'))
		{
			c = str[i];
			if (str[i + 1])
				i++;
		}
		if (str[i] == c)
			c = '*';
		i++;
	}
	return (0);
}

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
	if (too_many_redirection(str))
		return (1);
	if (contradicting_redir(str))
		return (1);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (no_words_after(str, i))
			{
				printf("bash: syntax error near unexpected token 'newline'\n");
				return (1);
			}
		}
		i++;
	}
	if (ft_check_multiple_operator(str))
		return (1);
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
	if (unexpected_pipe(str) == 1)
	{
		ft_printf("bash: syntax error near unexpected token 'newline'\n");
		return (2);
	}
	if (unexpected_pipe(str) == 2)
	{
		ft_printf("bash: syntax error near unexpected token '|'\n");
		return (2);
	}
	if (ft_error_shift_operator_2(str))
		return (2);
	return (0);
}
