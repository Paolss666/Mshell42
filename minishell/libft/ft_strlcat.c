/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:19:55 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/15 15:35:07 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;

	i = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (size < len_dst + 1)
		return (size + len_src);
	if (size > len_dst + 1)
	{
		while (src[i] && (len_dst + 1 + i) < size)
		{
			dst[len_dst + i] = src[i];
			i++;
		}
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

// int main(void)
// {
// 	char *src = "lol";
// 	char *dst = NULL;
// 	char *dst1 = NULL;
// 	int		size = 0;
// 	printf("%zu \n", ft_strlcat(dst, src, size));
// 	printf("%zu", strlcat(dst1, src, size));
//  }
