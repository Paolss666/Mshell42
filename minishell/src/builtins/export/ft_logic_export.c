/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:35 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 17:19:49 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"



int	found_export(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "export") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "\"export\"") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "\'export\'") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

// Funzione per lo swap di due nodi nella lista concatenata
void	ft_swap(t_exp *a, t_exp *b)
{
	char	*temp;

	temp = a->path;
	a->path = b->path;
	b->path = temp;
}

/* serve a ordinare la lista in ordine ASCII alpha */
void	export_env_sort(t_exp *exp_env)
{
	int		swap;
	t_exp	*next;
	t_exp	*current;

	swap = 1;
	if (!exp_env)
		return ((void)0);
	while (swap)
	{
		current = exp_env;
		swap = 0;
		while (current->next)
		{
			next = current->next;
			if (ft_strcmp(current->path, next->path) > 0)
			{
				ft_swap(current, next);
				swap = 1;
			}
			current = current->next;
		}
	}
}

char	*modif_path_for_export(t_envp *enviroment)
{
	char	*egual_position;
	char	*value;
	char	*name;
	char	*temp_name;
	char	*tmp_value;

	egual_position = ft_strchr(enviroment->path, '=');
	name = ft_substr(enviroment->path, 0, egual_position - enviroment->path);
	if (!name || garbagge(ADD, name, ENV))
		return (garbagge(FREE, egual_position, ENV), NULL);
	value = ft_strdup(egual_position + 1);
	if (!value || garbagge(ADD, value, ENV))
		return (garbagge(FREE, egual_position, ENV), garbagge(FREE, name, ENV),
			NULL);
	temp_name = ft_strjoin("export ", name);
	if (!temp_name || garbagge(ADD, temp_name, ENV))
		return (NULL);
	tmp_value = ft_strjoin(temp_name, "=\"");
	if (!tmp_value || garbagge(ADD, tmp_value, ENV))
		return (garbagge(FREE, temp_name, ENV), NULL);
	value = ft_strjoin(tmp_value, value);
	if (!value)
		return (NULL);
	return (value);
}

t_exp	*init_export(t_envp *enviroment)
{
	t_exp	*new_export;

	new_export = (t_exp *)malloc(sizeof(t_exp));
	if (!new_export || garbagge(ADD, new_export, ENV))
		return (garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->path = modif_path_for_export(enviroment);
	if (!new_export || garbagge(ADD, new_export->path, ENV))
		return (garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->path = ft_strjoin(new_export->path, "\"");
	if (!new_export->path || garbagge(ADD, new_export->path, ENV))
		return (garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->name = NULL;
	new_export->value = ft_strdup(ft_strchr(new_export->path, '='));
	if (!new_export->value || garbagge(ADD, new_export->value, ENV))
		return (garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->next = NULL;
	return (new_export);
}
