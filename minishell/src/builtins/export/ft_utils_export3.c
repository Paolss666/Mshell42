/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:31:52 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:50:04 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	add_export_variable_pro(char *line, char *found_equal, t_exp **export,
		t_exp *check_equal_list)
{
	char	*check_name_v;
	char	*name_v;
	char	*name_join_guimet;
	char	*check_equal;

	name_v = ft_strdup(line);
	if (!name_v || garbagge(ADD, name_v, ENV))
		return (-1);
	name_join_guimet = ft_strjoin(name_v, "=\"");
	if (!name_join_guimet || garbagge(ADD, name_join_guimet, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), -1);
	check_equal = ft_strjoin("export ", name_join_guimet);
	if (!check_equal || garbagge(ADD, check_equal, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), -1);
	check_name_v = ft_strjoin("export ", name_v);
	if (!check_name_v || garbagge(ADD, check_name_v, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), -1);
	if (check_export_variable_exists(check_equal, check_name_v,
			&check_equal_list))
		return (0);
	add_list_export(name_v, found_equal, export);
	return (0);
}

void	add_both_list(t_exp **export, t_envp **enviroment, char *name_v,
		char *value)
{
	add_environment_variable(enviroment, name_v, value);
	add_export_variable(export, name_v, value);
}

t_envp	*find_in_environment_list(t_envp *enviroment, char *name_v)
{
	while (enviroment != NULL && ft_strncmp(enviroment->path, name_v,
			ft_strlen(name_v)) != 0)
		enviroment = enviroment->next;
	return (enviroment);
}

t_exp	*find_in_export_list(t_exp *export, char *name_v)
{
	char	*good_path;

	good_path = ft_strjoin("export ", name_v);
	if (!good_path || garbagge(ADD, good_path, ENV))
		return (NULL);
	while (export != NULL && ft_strncmp(export->path, good_path,
			ft_strlen(good_path)) != 0)
		export = export->next;
	garbagge(FREE, good_path, ENV);
	return (export);
}

void	logic_add_in_exp_env(t_envp **enviroment, t_exp **export, t_v *v,
		char *modif_variable)
{
	t_envp	*current;
	t_exp	*new_upgrade_exp;

	current = find_in_environment_list(*enviroment, v->name);
	new_upgrade_exp = find_in_export_list(*export, v->name);
	if (current && new_upgrade_exp)
	{
		found_name_both_env(v->value, v->name, modif_variable, current);
		found_name_both_expo(modif_variable, v->value, v->name,
			new_upgrade_exp);
	}
	else if (!current && new_upgrade_exp)
	{
		current = add_node_to_end(enviroment, v->name, v->value);
		found_name_v_only_in_export(new_upgrade_exp, v->name, v->value);
	}
	else
		add_both_list(export, enviroment, v->name, v->value);
}
