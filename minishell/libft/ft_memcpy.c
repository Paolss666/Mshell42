/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:10:58 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/06 15:36:02 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*pnt_dest;
	unsigned char		*pnt_src;

	pnt_dest = (unsigned char *)dest;
	pnt_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		pnt_dest[i] = pnt_src[i];
		i++;
	}
	dest = (void *)pnt_dest;
	return (pnt_dest);
}
