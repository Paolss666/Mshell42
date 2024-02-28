/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:04:26 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/10 12:26:36 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: L’adresse du pointeur vers le premier élément
// de la liste.
// new: L’adresse du pointeur vers l’élément à
// rajouter à la liste.

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int main(int argc, char **argv)
// {
//   if (argc != 3)
//     return (1);
//   t_list  *test1;
//   t_list  *test2;

//   test1 = ft_lstnew(argv[1]);
//   test2 = ft_lstnew(argv[2]);

//   printf("Contenu 1er élément :\t%s\test2.next :\t%p\n",
// (char *)test1->content, test1->next);
//   printf("Contenu 2eme élément :\t%s\test2.next :\t%p\n", 
//(char *)test2->content, test2->next);
//   return (0);
// }