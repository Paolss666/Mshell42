/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:52:07 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/08 21:31:25 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_alone(char *s)
{
	if (s[1] || s[1] == ' ' || s[1] == '\"' || s[1] == '$')
		return (1);
	return (0);
}

int	found_dollar_alone(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i] == ' ')
			i++;
		i++;
	}
	return (0);
}

int	is_valid_variable_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || (c == '_') || (c == '?'));
}

char	*ft_strnjoin(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	char	*result;
	size_t	j;

	len_s1 = 0;
	len_s2 = 0;
	result = NULL;
	while (s1[len_s1])
		len_s1++;
	while (s2[len_s2] && len_s2 < n)
		len_s2++;
	result = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	i = len_s1;
	j = 0;
	while (s2[j] && j < n)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

t_expand	*init_structure_expand(int i, int err, char *dollar)
{
	t_expand	*expand;

	expand = (t_expand *)malloc(sizeof(t_expand));
	if (!expand || garbagge(ADD, expand, PARS))
		return (NULL);
	expand->dollar = ft_strdup(dollar);
	if (!expand->dollar || garbagge(ADD, expand->dollar, PARS))
		return (garbagge(FREE, expand, PARS), NULL);
	expand->i = i;
	expand->err = err;
	return (expand);
}
