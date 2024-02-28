/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:52:11 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/08 18:26:13 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Applique la fonction ’f’ à chaque caractère de la
// chaîne de caractères passée en argument pour créer
// une nouvelle chaîne de caractères (avec malloc(3))
// résultant des applications successives de ’f’.

// s: La chaîne de caractères sur laquelle itérer.
// f: La fonction à appliquer à chaque caractère

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*new_s;

	i = 0;
	len_s = 0;
	if (!s || !f)
		return (0);
	len_s = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * len_s + 1);
	if (!new_s)
		return (NULL);
	while (i < len_s)
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

// char 	f_asseye(unsigned int i, char c)
// {
// 	char s;
// 	s = c + i;
// 	return(s);
// }

// int main()
// {
// 	char str[] = "abc";
// 	char *str2;
// 	str2 = ft_strmapi(str, *f_asseye);
// 	printf("%s\n",str2);
// }