/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:26:07 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/27 18:19:44 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_eval_format(va_list args, const char format)
{
	int		ret;

	ret = 0;
	if (format == 'c')
		ret += ft_print_char(va_arg(args, int));
	if (format == 'd' || format == 'i')
		ret += ft_print_int(va_arg(args, int));
	if (format == 's')
		ret += ft_print_str(va_arg(args, char *));
	if (format == 'p')
		ret += ft_print_ptr(va_arg(args, unsigned long));
	if (format == '%')
		ret += write(1, "%", 1);
	if (format == 'x')
		ret += ft_print_hex(va_arg(args, unsigned int), LOWER_HEX_BASE);
	if (format == 'X')
		ret += ft_print_hex(va_arg(args, unsigned int), UPPER_HEX_BASE);
	if (format == 'u')
		ret += ft_print_uns_int(va_arg(args, unsigned int));
	return (ret);
}
