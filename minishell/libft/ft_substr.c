/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:13:16 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/12 09:40:24 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*new_s;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			new_s[j] = s[i];
			j++;
		}
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}

// int main(void)
// {
// 	char str[] ="michiamoNico";
// 	printf("%s\n", ft_substr(str,8,4));
// }
