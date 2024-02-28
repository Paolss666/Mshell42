/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:05:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/27 18:34:56 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*new_s;
	long	number;
	int		nblen;

	nblen = ft_nblen(n);
	number = n;
	new_s = (char *)malloc(sizeof(char) * nblen + 1);
	if (!new_s)
		return (NULL);
	if (number < 0)
	{
		new_s[0] = '-';
		number = -number;
	}
	if (number == 0)
		new_s[0] = '0';
	new_s[nblen--] = '\0';
	while (number)
	{
		new_s[nblen] = number % 10 + 48;
		nblen--;
		number = number / 10;
	}
	return (new_s);
}
