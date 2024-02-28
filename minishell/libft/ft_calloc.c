/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:09:59 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/15 18:37:58 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*elemt;
	int		over;

	over = (int)(size * nmemb);
	if (size)
	{
		if (nmemb != ((size_t)over / size))
			return (NULL);
	}
	elemt = (void *)malloc(nmemb * size);
	if (elemt == 0)
		return (NULL);
	ft_bzero(elemt, nmemb * size);
	return (elemt);
}
