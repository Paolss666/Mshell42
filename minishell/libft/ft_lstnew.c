/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:52:22 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/10 10:35:34 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Alloue (avec malloc(3)) et renvoie un nouvel
// élément. La variable membre ’content’ est
// initialisée à l’aide de la valeur du paramètre
// ’content’. La variable ’next’ est initialisée à NULL

t_list	*ft_lstnew(void *content)
{
	t_list	*new_t;

	new_t = malloc(sizeof(t_list));
	if (!new_t)
		return (NULL);
	new_t->content = content;
	new_t->next = NULL;
	return (new_t);
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