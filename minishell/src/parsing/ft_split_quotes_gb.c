/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_gb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:00 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/01 17:47:32 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int ft_count_w(const char *s, char c)
{
    size_t i;
    size_t n;

    n = 0;
    i = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if ((i == 0 || s[i - 1] == c) && s[i] != c)
            n++;
        i++;
    }
    return (n);
}

static size_t ft_strl_c(const char *s, char c)
{
    size_t i;

    i = 0;
    while (s[i] != c && s[i])
        i++;
    return (i);
}

static void ft_array(char **array, const char *s, char c)
{
    size_t i;
    size_t j;
    t_boolean swtc;
    size_t n_words;

    swtc = FALSE;
    i = 0;
    j = 0;
    n_words = ft_count_w(s, c);
    if (!s)
        return ;
    while (s[j] && i < n_words)
    {
        if (s[j] == '\'' || s[j] == '\"')
            swtc = !swtc; // Toggle in_quote when encountering quotes
        if (s[j] == c && !swtc)
            swtc = FALSE; // Reset in_quote if delimiter found outside quotes
        else if (s[j] != c && !swtc && s[j] != '\'' && s[j] != '\"')
        {
            array[i] = (char *)malloc(ft_strl_c(&(s[j]), c) + 1);
            if (!array[i])
                return ;
            swtc = TRUE;
            i++;
        }
        j++;
    }
}

static void ft_cpy_array(char **array, const char *s, char c)
{
    t_boolean start_cpy;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    start_cpy = FALSE;
    if (!s)
        return ;
    while (s[j])
    {
        if (s[j] == c && !start_cpy)
            start_cpy = FALSE;
        else if ((s[j] != c || start_cpy) && s[j] != '\'' && s[j] != '\"')
        {
            if (!start_cpy)
                start_cpy = TRUE;
            array[i] = (char *)malloc(ft_strl_c(&(s[j]), c) + 1);
            if (!array[i])
                return ;
            ft_strlcpy(array[i], &(s[j]), ft_strl_c(&(s[j]), c) + 1);
            i++;
        }
        j++;
    }
}

char **ft_split_quotes_gb(char const *s, char c)
{
    char **array;

    array = (char **)malloc((ft_count_w(s, c) + 1) * sizeof(char *));
    if (!array)
        return (NULL);
    ft_array(array, s, c);
    ft_cpy_array(array, s, c);
    array[ft_count_w(s, c)] = NULL;
    return (array);
}