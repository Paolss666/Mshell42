/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:00:34 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/27 18:19:15 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_unsigned_nbr_fd(unsigned int n, int fd)
{
	if (fd < 0)
		return ;
	if (n > 9)
		ft_put_unsigned_nbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + 48, fd);
}

int	ft_print_uns_int(unsigned int n)
{
	ft_put_unsigned_nbr_fd(n, 1);
	return (ft_cntdgt(n, 10));
}
