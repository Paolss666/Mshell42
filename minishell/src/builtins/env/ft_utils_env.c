/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:48:34 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 12:52:23 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_list_envp(t_envp *head)
{
	t_envp	*current;

	if (!head)
	{
		current = (t_envp *)malloc(sizeof(t_envp));
		if (!current || garbagge(ADD, current, ENV))
			return ((void)0);
		current->name = NULL;
		current->path = NULL;
		current->value = NULL;
		head = current;
		return ((void)0);
	}
	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->path);
		current = current->next;
	}
}

char	*found_shlvl_init(char *env)
{
	int		n;
	char	*value;

	value = NULL;
	n = 0;
	if (!env)
		return (NULL);
	if ((ft_strncmp(env, "SHLVL=", 6) == 0))
	{
		value = ft_strchr(env, '=') + 1;
		n = ft_atoi(value) + 1;
		value = ft_itoa(n);
		if (!value || garbagge(ADD, value, ENV))
			return (NULL);
		env = ft_strjoin("SHLVL=", value);
		if (!env || garbagge(ADD, env, ENV))
			return (garbagge(FLUSH, NULL, ALL), exit(124), NULL);
		return (env);
	}
	return (NULL);
}
