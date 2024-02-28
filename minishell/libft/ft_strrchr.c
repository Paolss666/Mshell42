/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:01:19 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/11 14:23:42 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*new_s;
	char		find;
	size_t		lenstr;

	new_s = (char *)s;
	find = (unsigned char)c;
	lenstr = ft_strlen(s);
	while (lenstr > 0)
	{
		if (new_s[lenstr] == find)
			return (&new_s[lenstr]);
		lenstr--;
	}
	if (new_s[lenstr] == find)
		return (new_s);
	return (NULL);
}
