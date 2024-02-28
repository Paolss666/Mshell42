/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_echo3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:41:25 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:44:48 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*find_variable_value(char *var_name, t_envp *enviroment, int e_st)
{
	char	*found_egual;
	char	*value;

	value = NULL;
	if (!var_name)
		return (NULL);
	if (!ft_strcmp(var_name, "?"))
		return (logic_f_dollar_int(var_name, e_st));
	while (enviroment != NULL)
	{
		if (ft_strcmp(enviroment->name, var_name) == 0)
		{
			found_egual = ft_strchr(enviroment->path, '=');
			value = ft_strdup(found_egual + 1);
			if (!value || garbagge(ADD, value, ENV))
				return (ft_putstr_fd("Fail malloc strdup\n", 2), NULL);
			return (value);
		}
		else
			enviroment = enviroment->next;
	}
	return (NULL);
}