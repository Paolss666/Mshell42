/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_gogo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:31:38 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/08 20:38:47 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int ft_isspace(char c)
{
    if (c == ' ' || (c >= '\t' && c <= '\r'))
        return (0);
    return (1);
}

void ft_inc_quote(char c, int *d_q,  int *s_q)
{
    if (c == '"' && *s_q % 2 == 0)
        (*d_q)++;
    else if (c == '\'' && *d_q % 2 == 0)
        (*s_q)++;
}

int	ft_count_word(const char *s)
{
	size_t	i;
	size_t	n;
    int d_q;
    int s_q;

	n = 0;
	i = 0;
    d_q = 0;
    s_q = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && d_q % 2 == 0 && s_q % 2 == 0 && ft_isspace(s[i]) == 0)
        {
            // printf("1er WHILE s[%ld] = |%c|\n", i, s[i]);
			ft_inc_quote(s[i++], &d_q, &s_q);
        }
		if (s[i] && (d_q % 2 == 1 || s_q % 2 == 1
				|| (d_q % 2 == 0 && s_q % 2 == 0 && ft_isspace(s[i]) == 1)))
		{
            // printf(" IF s[%ld] = |%c|\n", i, s[i]);
			ft_inc_quote(s[i++], &d_q, &s_q);
			n++;
		}
		while (s[i] && (d_q % 2 == 1 || s_q % 2 == 1
				|| (d_q % 2 == 0 && s_q % 2 == 0 && ft_isspace(s[i]) == 1)))
        {
            // printf(" 2 WHILE s[%ld] = |%c|\n", i, s[i]);
			ft_inc_quote(s[i++], &d_q, &s_q);
        }
	}
    printf("COUNT_W n = %ld\n", n);
	return (n);
}
