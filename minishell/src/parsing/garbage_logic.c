/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:47:27 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 15:47:42 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_gb	*init_gb(void)
{
	t_gb *gb;

	gb = (t_gb *)malloc(sizeof(t_gb));
	if (gb)
	{
		gb->list = 0;
		gb->p = 0;
	}
	return (gb);
}

int	garbagge(int rule, void *p, int list)
{
	static t_list	*a = NULL;
	static t_list	*b = NULL;
	static t_list	*c = NULL;
	t_gb			*gb;

	gb = init_gb();
	if (!gb)
		return (1);
	gb->list = list;
	gb->p = p;
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
	free(gb);
	return (0);
}