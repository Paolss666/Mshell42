/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:54:23 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/11 18:57:14 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*sn1;
	const unsigned char	*sn2;

	i = 0;
	sn1 = (const unsigned char *)s1;
	sn2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (sn1[i] != sn2[i])
			return (sn1[i] - sn2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char str1[] = "nicol";
// 	char str2[] = "n";
// 	int  l = 2;
// 	printf("%d", memcmp(str1, str2, l));
// 	printf("\n");
// 	printf("%d", ft_memcmp(str1, str2, l));
// }
