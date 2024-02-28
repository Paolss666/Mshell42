/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:19:44 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/15 17:51:59 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new_s;

	new_s = NULL;
	if (s1 != 0 || set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		new_s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (!new_s)
			return (NULL);
		if (new_s)
			ft_strlcpy(new_s, &s1[start], end - start + 1);
	}
	return (new_s);
}

// int	main(void)
// {
// 	char *str = "a-clQuesta e' la frase-ca";
// 	char *set = "-ac";

// 	printf("%s",ft_strtrim(str, set));
// }