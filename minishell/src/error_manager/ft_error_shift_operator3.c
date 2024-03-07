/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_shift_operator3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:26:08 by armeyer           #+#    #+#             */
/*   Updated: 2024/03/06 17:47:19 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	too_many_redir_left(int count)
{
	if (count == 4)
	{
		printf("bash: syntax error near unexpected token '<'\n");
		return (1);
	}
	if (count == 5)
	{
		printf("bash: syntax error near unexpected token '<<'\n");
		return (1);
	}
	if (count > 5)
	{
		printf("bash: syntax error near unexpected token '<<<'\n");
		return (1);
	}
	return (0);
}


int	too_many_redir_right(int count)
{
	if (count == 3)
	{
		printf("bash: syntax error near unexpected token '>'\n");
		return (1);
	}
	if (count > 3)
	{
		printf("bash: syntax error near unexpected token '>>'\n");
		return (1);
	}
	return (0);
}

int	count_redir(char *str, char c)
{
	int	i;
	int	temp;
	int	count;

	i = 0;
	temp = 0;
	while (str[i] != '\0')
	{
		count = 0;
		if (str[i + 1] && str[i] == c)
		{
			while (str[i] && str[i] == c)
			{
				count++;
				i++;
			}
		}
		if (count > temp)
			temp = count;
		i++;
	}
	count = temp;
	return (count);
}

int	too_many_redirection(char *str)
{
	int		count;

	if(!str)
		return (0);
	count = count_redir(str, '>');
	if (too_many_redir_right(count))
		return (1);
	count = count_redir(str, '<');
	if (too_many_redir_left(count))
		return (1);
	if (special_redir_case(str))
		return (1);
	return (0);
}

int	check_multipless_left(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
		{
			while (str[i] != '\0' && str[i] == '<')
			{
				count++;
				i++;
			}
			if (count > 5)
			{
				printf("bash: syntax error near unexpected token '<<<'\n");
				return (1);
			}
			count = 0;
		}
		i++;
	}
	return (0);
}
