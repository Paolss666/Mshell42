/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:44:19 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/12 14:11:03 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// st: L’élément à free
// del: L’adresse de la fonction permettant de
// supprimer le contenu de l’élément.
// Libère la mémoire de l’élément passé en argument en
// utilisant la fonction ’del’ puis avec free(3). La
//  mémoire de ’next’ ne doit pas être free.

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		(*del)(lst->content);
		free(lst);
	}
}
