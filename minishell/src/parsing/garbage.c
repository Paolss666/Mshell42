/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:24:17 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 10:26:27 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	del(void *p)
{
	free(p);
	p = NULL;
}


void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;
	t_list	*prev;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	prev = NULL;
	while (cur != NULL)
	{
		if (cmp(cur->content, data_ref) == 0)
		{
			if (!prev)
				*begin_list = cur->next;
			else
				prev->next = cur->next;
			ft_lstdelone(cur, del);
			if (!prev)
				cur = *begin_list;
			else
				cur = prev->next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

int	cmp(void *p1, void *p2)
{
	if (p1 == p2)
		return (0);
	return (1);
}

void	logic_garbage_clear(int list, t_list *a, t_list *b, t_list *c)
{
	if (list == PARS)
		ft_lstclear(&a, del);
	else if (list == EX)
		ft_lstclear(&b, del);
	else if (list == ENV)
		ft_lstclear(&c, del);
	else if (list == ALL)
	{
		ft_lstclear(&a, del);
		ft_lstclear(&b, del);
		ft_lstclear(&c, del);
	}
}



int	garbagge(int rule, void *p, int list)
{
	static t_list	*a = NULL;
	static t_list	*b = NULL;
	static t_list	*c = NULL;
	t_list			*node;

	if (rule == ADD)
	{
		node = ft_lstnew(p);
		if (!node)
			return (free(p), 1);
		if (list == PARS)
			ft_lstadd_back(&a, node);
		else if (list == EX)
			ft_lstadd_back(&b, node);
		else if (list == ENV)
			ft_lstadd_back(&c, node);
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
	return (0);
}
