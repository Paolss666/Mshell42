/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:31:04 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:38:45 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*modif_variable_exp(char *name_v, char *value)
{
	char	*good_path;
	char	*tmp_tree;
	char	*tmp2_tree;

	good_path = ft_strjoin(name_v, "=\"");
	if (!good_path || garbagge(ADD, good_path, ENV))
		return (garbagge(FLUSH, NULL, ALL), NULL);
	tmp_tree = ft_strjoin(value, "\"");
	if (!tmp_tree || garbagge(ADD, tmp_tree, ENV))
		return (garbagge(FLUSH, NULL, ALL), NULL);
	tmp2_tree = ft_strjoin(good_path, tmp_tree);
	if (!tmp2_tree || garbagge(ADD, tmp2_tree, ENV))
		return (garbagge(FLUSH, NULL, ALL), NULL);
	garbagge(FREE, good_path, ENV);
	garbagge(FREE, tmp_tree, ENV);
	return (tmp2_tree);
}

void	add_export_variable(t_exp **export, char *name_v, char *value)
{
	t_exp	*new_export;
	char	*tmp2_tree;
	t_exp	*new_current;
	t_exp	*last_exp;

	new_export = (t_exp *)malloc(sizeof(t_exp));
	if (!new_export || garbagge(ADD, new_export, ENV))
		return (garbagge(FLUSH, NULL, ALL), (void)0);
	tmp2_tree = modif_variable_exp(name_v, value);
	new_export->value = value;
	new_export->path = ft_strjoin("export ", tmp2_tree);
	if (!new_export->path || garbagge(ADD, new_export->path, ENV))
		return (garbagge(FLUSH, NULL, ALL), (void)0);
	new_export->name = name_v;
	new_export->next = NULL;
	new_current = *export;
	if (!new_current)
		new_current = new_export;
	else
	{
		last_exp = new_current;
		while (last_exp->next != NULL)
			last_exp = last_exp->next;
		last_exp->next = new_export;
	}
}

int	check_export_variable_exists(char *check_equal, char *check_name_v,
		t_exp **check_equal_list)
{
	t_exp	*prev;
	t_exp	*current;

	prev = NULL;
	current = *check_equal_list;
	while (current)
	{
		if (ft_strncmp(current->path, check_equal, ft_strlen(check_equal)) == 0
			|| ft_strncmp(current->path, check_name_v,
				ft_strlen(check_name_v)) == 0)
		{
			if (ft_strchr(check_equal, '='))
				return (1);
			if (prev)
				prev->next = current->next;
			else
				*check_equal_list = current->next;
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

t_exp	*ft_new_export(char *name_v, char *value)
{
	t_exp	*new_export;
	char	*join_name_value;

	new_export = (t_exp *)malloc(sizeof(t_exp));
	if (!new_export || garbagge(ADD, new_export, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	join_name_value = ft_strjoin(name_v, value);
	if (!join_name_value || garbagge(ADD, join_name_value, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->path = ft_strjoin("export ", join_name_value);
	if (!new_export->path || garbagge(ADD, new_export->path, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->name = ft_strdup(name_v);
	if (!new_export->name || garbagge(ADD, new_export->name, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->value = ft_strdup(value);
	if (!new_export->value || garbagge(ADD, new_export->value, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	new_export->next = NULL;
	return (new_export);
}

t_exp	*add_list_export(char *name_v, char *found_equal, t_exp **export)
{
	t_exp	*new_export;
	char	*value;
	t_exp	*last_exp;

	if (!found_equal)
	{
		found_equal = ft_strdup("");
		if (!found_equal || garbagge(ADD, found_equal, ENV))
			return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	}
	value = found_equal;
	new_export = ft_new_export(name_v, value);
	if (*export == NULL)
		*export = new_export;
	else
	{
		last_exp = *export;
		while (last_exp->next != NULL)
			last_exp = last_exp->next;
		last_exp->next = new_export;
	}
	return (new_export);
}
