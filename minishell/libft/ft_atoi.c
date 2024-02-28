/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:51:53 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/08 11:58:57 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	number;
	int	parity;

	number = 0;
	parity = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			parity++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = 10 * number + nptr[i] - 48;
		i++;
	}
	if (parity % 2 == 0)
		return (number);
	else
		return (-number);
}
