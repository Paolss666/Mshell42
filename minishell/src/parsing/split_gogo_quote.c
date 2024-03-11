/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_gogo_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:33:34 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 22:14:20 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_test(char c, const char *c1, const char *cm1, t_quote q)
{
	if (!c)
		return (1);
	if (q.d_q % 2 == 1)
		return (0);
	if (q.s_q % 2 == 1)
		return (0);
	if (ft_isspace(c) == 0)
		return (1);
	if (c != '"' && c != 39)
		return (0);
	if (c == '"' && ((c1 && *c1 && ft_isspace(*c1) == 1)
			|| (cm1 && ft_isspace(*cm1) == 1)))
		return (0);
	if (c == 39 && ((c1 && *c1 && ft_isspace(*c1) == 1) || (cm1
				&& ft_isspace(*cm1) == 1)))
		return (0);
	else
		return (1);
}


size_t	ft_strl_quote(const char *s)
{
	size_t	i;
	size_t	c;
	t_quote	q;

	i = 0;
	c = 0;
	q.d_q = 0;
	q.s_q = 0;
	while (s[i] && ft_isspace(s[i]) == 0)
		i++;
	if (i == 0 && s[i])
	{
		ft_inc_quote(s[i++], &q.d_q, &q.s_q);
		c++;
	}
	while (s[i] && ft_test(s[i], &s[i + 1], &s[i - 1], q) == 0)
	{
		ft_inc_quote(s[i++], &q.d_q, &q.s_q);
		c++;
	}
	return (c);
}


void	ft_strlcpy_msh_quote(char *token,
	const char *src, size_t size, size_t *k)
{
	t_quote	q;

	q = ini_for_quote();
	while (size > 0 && src[q.i] && q.j < (size - 1))
	{
		if (q.i == 0 && src[q.i])
		{
			ft_inc_quote(src[q.i], &q.d_q, &q.s_q);
			token[q.j++] = src[q.i++];
		}
		else if (src[q.i]
			&& ft_test(src[q.i], &src[q.i + 1], &src[q.i - 1], q) == 0)
		{
			ft_inc_quote(src[q.i], &q.d_q, &q.s_q);
			token[q.j++] = src[q.i++];
		}
	}
	token[q.j] = '\0';
	cook(k, q, src);
}

static void	ft_array(char **array, const char *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		count;
	t_boolean	swtc;
	size_t		n_words;

	(void)c;
	swtc = 0;
	i = 0;
	j = 0;
	n_words = (ft_count_word(s));
	if (!s)
		return ;
	while (s[j] && i < n_words)
	{
		count = ft_strl_quote(&(s[j]));
		array[i] = (char *)malloc(count + 1);
		if (!array[i] || garbagge(ADD, array[i], PARS))
			return ;
		if (count >= 0)
			ft_strlcpy_msh_quote(array[i], s + j, count + 1, &j);
		i++;
	}
}

char	**ft_split_garbage_gogo_quote(char const *s, char c)
{
	char	**array;

	(void)c;
	array = (char **)malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (!array || garbagge(ADD, array, PARS))
		return (NULL);
	ft_array(array, s, c);
	array[ft_count_word(s)] = NULL;
	return (array);
}
