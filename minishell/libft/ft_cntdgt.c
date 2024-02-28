/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntdgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:31:06 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/20 17:52:46 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_cntdgt(unsigned long long n, int base)
{
	unsigned long long	ret;

	ret = 0;
	if (n == 0)
		ret++;
	while (n)
	{
		ret++;
		n = n / base;
	}
	return (ret);
}
