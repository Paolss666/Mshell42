/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:47:27 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 03:08:33 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_gb	*init_gb(int list, void *p)
{
	t_gb	*gb;

	gb = (t_gb *)malloc(sizeof(t_gb));
	if (gb)
	{
		gb->list = list;
		gb->p = p;
	}
	return (gb);
}

int	garbagge(int rule, void *p, int list)
{
	static t_list	*a = NULL;
	static t_list	*b = NULL;
	static t_list	*c = NULL;
	t_gb			*gb;

	gb = init_gb(list, p);
	if (!gb)
		return (1);
	if (rule == ADD)
	{
		if (logic_add_back(&a, &b, &c, gb))
			return (free(gb->p), 1);
	}
	else if (rule == FLUSH)
		logic_garbage_clear(list, a, b, c);
	else if (rule == FREE)
	{
		if (list == PARS)
			ft_list_remove_if(&a, p, cmp);
		else if (list == EX)
			ft_list_remove_if(&b, p, cmp);
		else if (list == ENV)
			ft_list_remove_if(&c, p, cmp);
	}
	return (free(gb), 0);
}

char	*ft_strndup_g(const char *src, size_t n)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	if (n < len)
		len = n;
	dest = (char *)malloc(len + 2);
	if (!dest || garbagge(ADD, dest, PARS))
		return (NULL);
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}
