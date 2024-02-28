/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:06:59 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/06 15:26:53 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The  bzero()  function  erases  the  data in the n bytes of the memory 
//starting at the location pointed to by s, by writing zeros
// (bytes containing '\0') to that area.

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
