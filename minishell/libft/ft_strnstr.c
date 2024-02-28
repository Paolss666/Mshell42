/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:59:48 by npaolett          #+#    #+#             */
/*   Updated: 2023/08/22 14:22:18 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char const	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i + len);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char *str = "nicoooooooolo";
// 	char *str2  = "oolo";
// 	int	len = 3;

// 	printf("%s\n", ft_strnstr(str, str2, len));
// }