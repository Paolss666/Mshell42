/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_gogo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:31:38 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 22:15:06 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (0);
	return (1);
}

void	ft_inc_quote(char c, int *d_q, int *s_q)
{
	if (c == '"' && *s_q % 2 == 0)
		(*d_q)++;
	else if (c == '\'' && *d_q % 2 == 0)
		(*s_q)++;
}

int	ft_count_word(const char *s)
{
	t_quote	q;
	int		n;

	n = 0;
	q = ini_for_quote();
	if (!s)
		return (0);
	while (s[q.i])
	{
		while (s[q.i] && q.d_q % 2 == 0 && q.s_q % 2 == 0
			&& ft_isspace(s[q.i]) == 0)
			ft_inc_quote(s[q.i++], &q.d_q, &q.s_q);
		if (s[q.i] && (q.d_q % 2 == 1 || q.s_q % 2 == 1
				|| (q.d_q % 2 == 0 && q.s_q % 2 == 0
					&& ft_isspace(s[q.i]) == 1)))
		{
			ft_inc_quote(s[q.i++], &q.d_q, &q.s_q);
			n++;
		}
		while (s[q.i] && (q.d_q % 2 == 1 || q.s_q % 2 == 1
				|| (q.d_q % 2 == 0 && q.s_q % 2 == 0
					&& ft_isspace(s[q.i]) == 1)))
			ft_inc_quote(s[q.i++], &q.d_q, &q.s_q);
	}
	return (n);
}
