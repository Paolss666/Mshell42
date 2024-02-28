/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:55:59 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/15 17:34:24 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: L’adresse du pointeur vers un élément.
// del: L’adresse de la fonction permettant de
// supprimer le contenu d’un élément.
//
// Supprime et libère la mémoire de l’élément passé en
// paramètre, et de tous les éléments qui suivent, à
// l’aide de ’del’ et de free(3)
// Enfin, le pointeur initial doit être mis à NULL.

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst && del && *lst)
	{
		while (*lst && *del)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	}
}
