/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:13:05 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/08 18:46:55 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(((s1_len + s2_len + 1) * sizeof(char)));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(&str[s1_len], s2, s2_len + 1);
	return (str);
}

// int main(void)
// {
// 	char *str = "Nicola";
// 	char *str2 = "paols";

// 	printf("%s", ft_strjoin( str,str2));
// }
