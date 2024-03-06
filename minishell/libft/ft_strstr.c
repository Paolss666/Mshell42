/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:51:30 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/05 20:59:44 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strstr(const char *haystack, const char *needle)
{
    size_t hlen;
    size_t  nlen;
    const char *end;

    hlen = 0;
    nlen = 0;
    if (!haystack || !needle)
        return (NULL);
    hlen = ft_strlen(haystack);
    nlen = ft_strlen(needle);
    if (!nlen)
        return( (char *)haystack);
    if (hlen < nlen) 
        return (NULL);
    end = haystack + hlen - nlen;
    while (haystack <= end)
    {
        if (ft_strncmp(haystack, needle, nlen) == 0) 
            return ((char *)haystack);
        haystack++;
    }
    return (NULL);
}
