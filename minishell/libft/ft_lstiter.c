/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:42:23 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/10 15:52:48 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: L’adresse du pointeur vers un élément.
// f: L’adresse de la fonction à appliquer.
// itère sur la liste ’lst’ et applique la fonction
// ’f’ au contenu chaque élément.

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst && f)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
