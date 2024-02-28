/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:06:00 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/09 15:47:06 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

	// i = 0;
	// srclen = ft_strlen(src);
	// if (srclen + 1 < size)
	// 	ft_memcpy(dest, src, srclen + 1);
	// else if (size != 0)
	// {
	// 	ft_memcpy(dest, src, size - 1);
	// 	dest[size - 1] = '\0';
	// }
	// return (srclen);
