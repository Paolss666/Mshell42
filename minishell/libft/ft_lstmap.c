/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:59:33 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/11 11:52:28 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: L’adresse du pointeur vers un élément.
// f: L’adresse de la fonction à appliquer.
// del: L’adresse de la fonction permettant de
// supprimer le contenu d’un élément.
// Return: La nouvelle liste // NULL si l'alloc echoue
// Description:
// Itère sur la liste ’lst’ et applique la fonction
// ’f ’au contenu de chaque élément. Crée une nouvelle
// liste résultant des applications successives de
// ’f’. La fonction ’del’ est là pour détruire le
// contenu d’un élément si nécessaire.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	tmp = ft_lstnew(f(lst->content));
	if (!tmp)
		return (NULL);
	ptr = tmp;
	lst = lst->next;
	while (lst)
	{
		tmp->next = ft_lstnew(f(lst->content));
		if (!tmp->next)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (ptr);
}
