/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:45:51 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/27 18:19:34 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int n, const char *base)
{
	if (n >= 16)
		ft_print_hex(n / 16, base);
	if (n > 10)
		ft_putchar_fd(base[n % 16], 1);
	else
		ft_putchar_fd(base[n % 16], 1);
	return (ft_cntdgt(n, 16));
}
