/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_gogo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:06:25 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/08 20:38:50 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

int	ft_test(char c, const char *c1, const char *cm1, t_quote q)
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

int	ft_test_bis(char c, int *d_q, int *s_q)
{
    ft_inc_quote(c, d_q, s_q);
    // printf ("c |%c| d_q %d s_q %d\n", c, *d_q, *s_q);
	if (c != '"' && c != 39)
		return (0);
	if (c == '"' && *s_q % 2 == 1)
		return (0);
	if (c == '\'' && *d_q % 2 == 1)
		return (0);
	else {
        // printf ("RETOUR 1\n");
		return (1);
    }
}

size_t	ft_strl(const char *s)
{
	size_t	i;
    size_t  c;
    t_quote q;

	i = 0;
    c = 0;
    q.d_q = 0;
    q.s_q = 0;
    // printf("s = |%s|\n", s);
    while (s[i] && q.d_q % 2 == 0 && q.s_q % 2 == 0 && (s[i] == '"'
			|| s[i] == '\'' || ft_isspace(s[i]) == 0))
		ft_inc_quote(s[i++], &q.d_q, &q.s_q);
    if (i == 0 && s[i] && ft_test(s[i], &s[i + 1], NULL, q) == 0)
    {   
        // printf("s[%ld] = |%c|\n", i, s[i]);
        // ft_inc_quote(s[i++], &q.d_q, &q.s_q);
        if (ft_test_bis(s[i++], &q.d_q, &q.s_q) == 0) {
            // printf("s[%ld] = |%c|\n", i - 1, s[i - 1]);
            c++;
        }
    }
    while (s[i] && ft_test(s[i], &s[i + 1], &s[i - 1], q) == 0)
	{
        // printf("DANS LE WHILE\n");
        // printf("AVANT TEST BIS s[%ld] = |%c|\n", i, s[i]);
        // ft_inc_quote(s[i++], &q.d_q, &q.s_q);
		if (ft_test_bis(s[i++], &q.d_q, &q.s_q) == 0) {
            // printf("s[%ld] = |%c|\n", i - 1, s[i - 1]);
            c++;
        }
	}
	// *j += i;
	// while (s[i] != c && s[i])
	// 	i++;
    // printf("COUNT_L c = %ld\n", c);
	return (c);
}

// static void	ft_exec_strlcpy_msh(t_split *strs, const char *src, t_index *x,
// 		t_quote *q)
// {
// 	else if (ft_test_bis(src[x->i], q->d, q->s) == 0)
// 	{
// 		strs->data[x->j] = src[x->i++];
// 		x->j++;
// 	}
// 	else
// 		x->i++;
// }

void	ft_strlcpy_msh(char *token, const char *src, size_t size, size_t *k)
{
	size_t i;
    size_t j;
	t_quote	q;

    i = 0;
    j = 0;
    q.d_q = 0;
    q.s_q = 0;
	// if (begin > -1)
	// 	ft_inc_quote(src[0], &q.d_q, &q.s_q);
	// if (begin == -1 && (src[1] == '"' || src[1] == '\''))
	// 	strs->quote = 1;
	while (size > 0 && src[i] && j < (size - 1))
	{
        if (src[i] && q.d_q % 2 == 0 && q.s_q % 2 == 0 && (src[i] == '"'
			|| src[i] == '\'' || ft_isspace(src[i]) == 0))
	    	ft_inc_quote(src[i++], &q.d_q, &q.s_q);
        else if (i == 0 && src[i] && ft_test(src[i], &src[i + 1], NULL, q) == 0)
        {   
            if (ft_test_bis(src[i], &q.d_q, &q.s_q) == 0)
                token[j++] = src[i];
            i++;
            // ft_inc_quote(src[i], &q.d_q, &q.s_q);
            // token[j++] = src[i++];
        }
        else if (src[i] && ft_test(src[i], &src[i + 1], &src[i - 1], q) == 0)
        {
            if (ft_test_bis(src[i], &q.d_q, &q.s_q) == 0)
                token[j++] = src[i];
            i++;
            // ft_inc_quote(src[i], &q.d_q, &q.s_q);
            // token[j++] = src[i++];
        }
		// ft_inc_quote(src[i], &q.d_q, &q.s_q);
		// if (ft_test_ter(src[i], q) == 0 && ft_test_bis(src[x->i], q->d, q->s) == 0)
		// 	ft_exec_strlcpy_msh(token, src, &x, &q);
	}
	token[j] = '\0';
    if (k) {
        if (src[i])
            *k += i + 1;
        else
            *k += i;
        // printf("*k = %ld\n", *k);
    }
}

static void	ft_array(char **array, const char *s, char c)
{
	size_t		i;
	size_t		j;
    size_t      count;
	t_boolean	swtc;
	size_t		n_words;

    (void) c;
	swtc = 0;
	i = 0;
	j = 0;
	n_words = (ft_count_word(s));
	if (!s)
		return ;
	while (s[j] && i < n_words)
	{
		// if (s[j] == c)
		// 	swtc = FALSE;
		// else if (s[j] != c && swtc == FALSE)
		// {
            count = ft_strl(&(s[j]));
			array[i] = (char *)malloc(count + 1);
			if (!array[i] || garbagge(ADD, array[i], PARS))
				return ;
            if (count >= 0)
			    ft_strlcpy_msh(array[i], s + j, count + 1, &j);// penser a incrementer j
            printf("COUNT_W j = %ld\n", j);
            
			// swtc = TRUE;
			i++;
		// }
		// j++;
	}
}

char	**ft_split_garbage_gogo(char const *s, char c)
{
	char	**array;

    (void) c;
    printf("DEBUT SPLIT\n");
    printf("s = |%s|\n", s);

	array = (char **)malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (!array || garbagge(ADD, array, PARS))
		return (NULL);
	ft_array(array, s, c);
	// ft_cpy_array(array, s, c);
	array[ft_count_word(s)] = NULL;
    printf("FIN SPLIT\n");
    print_string_array(array);
    printf("\n\n\n\n\n\n\n");
	return (array);
}
