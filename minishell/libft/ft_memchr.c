/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:26:26 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/06 16:50:29 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy_str;

	cpy_str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cpy_str[i] == (unsigned char)c)
			return (&cpy_str[i]);
		i++;
	}
	return (NULL);
}
