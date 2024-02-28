/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:15:32 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/11 14:17:47 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	find;
	int		i;

	find = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == find)
			return (((char *)s + i));
		i++;
	}
	if (s[i] == find)
		return (((char *)s + i));
	return (0);
}

// int main(void)
// {
// 	char *s = "\0";
// 	int c = '\0' ;
// 	printf("ma ft :%s.\n", ft_strchr(s, c));
// 	printf("la vrai :%s." ,strchr(s, c));
// }