/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:40 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/27 18:19:28 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_ulong_hex(unsigned long long n)
{
	char			*base;

	base = LOWER_HEX_BASE;
	if (n >= 16)
		ft_print_ulong_hex(n / 16);
	if (n > 10)
		ft_putchar_fd(base[n % 16], 1);
	else
		ft_putchar_fd(base[n % 16], 1);
}

int	ft_print_ptr(unsigned long long n)
{
	char				*pref;

	pref = "0x";
	if ((void *)n == NULL)
		return (write(1, "(nil)", 5));
	ft_putstr_fd(pref, 1);
	ft_print_ulong_hex(n);
	return (ft_strlen(pref) + ft_cntdgt(n, 16));
}
