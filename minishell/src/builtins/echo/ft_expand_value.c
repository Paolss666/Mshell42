/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:30:37 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/08 21:55:07 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*cretion_sub_string(char *value, int len_tot, char *expanded_value)
{
	char	*sub_s;

	printf("PROCESS_CREATION\n");
	sub_s = ft_substr(value, 0, len_tot);
	if (!sub_s || garbagge(ADD, sub_s, PARS))
		return (garbagge(FLUSH, NULL, ALL), NULL);
	expanded_value = ft_strjoin(expanded_value, sub_s);
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	return (expanded_value);
}

char	*expnad_join_dollar(char *expanded_value, char *dollar)
{
	expanded_value = ft_strnjoin(expanded_value, dollar, 1);
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	return (expanded_value);
}

char	*expand_last_dollar(char *expanded_value, char *value)
{
	expanded_value = ft_strjoin(expanded_value, value);
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	return (expanded_value);
}

char	*expanded_var_value(char *var_value, char *expanded_value)
{
	if (var_value)
	{
		expanded_value = ft_strjoin(expanded_value, var_value);
		if (!expanded_value || garbagge(ADD, expanded_value, PARS))
			return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	}
	return (expanded_value);
}

void	join_not_expand(char **value, char **expanded_value)
{
	char *tmp;

	tmp = *expanded_value;
	*expanded_value = ft_strnjoin(*expanded_value, *value, 1);
	if (garbagge(ADD, *expanded_value, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	garbagge(FREE, tmp, PARS);
	(*value)++;
	while(**value && **value != '\'')
	{
		tmp = *expanded_value;
		*expanded_value = ft_strnjoin(*expanded_value, *value, 1);
		if (garbagge(ADD, *expanded_value, PARS))
			garbagge(FLUSH, NULL, ALL);
		garbagge(FREE, tmp, PARS);
		(*value)++;
	}
}

void	process_expand(char **value, char **expanded_value, t_expand *expand,
		t_envp *environment)
{
	char	*var_name;
	char	*var_value;

	printf("PROCESS_EXPAND\n");
	if (expand->dollar[1] == ' ' || !is_valid_variable_char(expand->dollar[1]))
	{
		*expanded_value = expnad_join_dollar(*expanded_value, expand->dollar);
		*value = expand->dollar + 1;
	}
	else
	{
		var_name = creation_var_name(1, expand->i, expand->dollar);
		var_value = find_variable_value(var_name, environment,
				expand->err);
		if (var_value)
			*expanded_value = expanded_var_value(var_value, *expanded_value);
		*value = expand->dollar + ft_strlen(var_name) + 1;
	}
}
