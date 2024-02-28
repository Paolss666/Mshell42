/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:59:30 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/08 17:03:39 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_count_w(const char *s, char c)
{
	size_t	i;
	size_t	n;

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

static size_t	ft_strl_c(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	ft_array(char **array, const char *s, char c)
{
	size_t		i;
	size_t		j;
	t_boolean	swtc;
	size_t		n_words;

	swtc = 0;
	i = 0;
	j = 0;
	n_words = (ft_count_w(s, c));
	if (!s)
		return ;
	while (s[j] && i < n_words)
	{
		if (s[j] == c)
			swtc = FALSE;
		else if (s[j] != c && swtc == FALSE)
		{
			array[i] = (char *)malloc(ft_strl_c(&(s[j]), c) + 1);
			if (!array[i] || garbagge(ADD, array[i], PARS))
				return ;
			swtc = TRUE;
			i++;
		}
		j++;
	}
}

static void	ft_cpy_array(char **array, const char *s, char c)
{
	t_boolean	start_cpy;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	start_cpy = 0;
	if (!s)
		return ;
	while (s[j])
	{
		if (s[j] == c)
			start_cpy = FALSE;
		else if (s[j] != c && start_cpy == FALSE)
		{
			ft_strlcpy(array[i], &(s[j]),
				ft_strl_c(&(s[j]), c) + 1);
			start_cpy = TRUE;
			i++;
		}
		j++;
	}
}

char	**ft_split_garbage(char const *s, char c)
{
	char	**array;

	array = (char **)malloc((ft_count_w(s, c) + 1) * sizeof(char *));
	if (!array || garbagge(ADD, array, PARS))
		return (NULL);
	ft_array(array, s, c);
	ft_cpy_array(array, s, c);
	array[ft_count_w(s, c)] = NULL;
	return (array);
}