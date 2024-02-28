/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:32:26 by npaolett          #+#    #+#             */
/*   Updated: 2023/05/08 19:07:31 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Applique la fonction ’f’ à chaque caractère de la
// chaîne de caractères transmise comme argument,
// et en passant son index comme premier argument.
// Chaque caractère est transmis par adresse à ’f’
// afin d’être modifié si nécessaire

// s: La chaîne de caractères sur laquelle itérer.
// f: La fonction à appliquer à chaque caractère.

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}

// static void    test_ft_upper(unsigned int i, char *c)
// {
//     if (i >= 0)
//         *c = *c - 32;
// }

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//         return (1);
//     void    *ptr_f = &test_ft_upper;
//     char    *str_buf;
//		str_buf = (char *)malloc((ft_strlen(argv[1]) + 1) * sizeof(char));
//     str_buf = argv[1];
//     ft_striteri(str_buf, ptr_f);
//     printf("%s\t<Doit être en MAJ", str_buf);
//     return (0);
// }