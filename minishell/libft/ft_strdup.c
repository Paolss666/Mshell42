/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:22:48 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/15 17:53:43 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*snew;

	snew = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!snew)
		return (NULL);
	ft_strlcpy(snew, s, ft_strlen(s) + 1);
	return (snew);
}

// int	main(void)
// {
// 	char *str = "lQuesta e' la frase di ";

// 	printf("%s" , ft_strdup(str));
// }