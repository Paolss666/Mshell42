/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:43:18 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 14:08:06 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*cretion_sub_string(char *value, int len_tot, char *expanded_value)
{
	char	*sub_s;

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