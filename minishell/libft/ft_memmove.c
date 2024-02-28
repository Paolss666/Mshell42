/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:12:22 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/12 13:12:34 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// pour calculer la fin des adresses, on ajoute la valeur de l'argument n 
//a l'adr de la zone a calcler puis -1 pour debuter dans le bn adr

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*p_dest;
	unsigned char			*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (p_src <= p_dest)
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n--)
		{
			*p_dest-- = *p_src--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

// int	main(void)
// {
// 	char    tab3[] = "abcdefghijklmno";
// 	char    tab3b[] = "abcdefghijklmno";

// 	  ft_memmove(tab3 + 1, tab3 + 2, sizeof(char) * 4);
// 		memmove(tab3b + 1, tab3b + 2, sizeof(char) * 4);
// 	printf("ft_memmove = %s\n   memmove = %s\n", tab3, tab3b);
// }