/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:52 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:49:29 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	found_name_both_env(char *value, char *name_v, char *modif_variable,
		t_envp *current)
{
	char	*temp_v;

	temp_v = NULL;
	if (modif_variable)
	{
		current->path = ft_strjoin(current->path, modif_variable);
		if (!current->path || garbagge(ADD, current->path, ENV))
			return (garbagge(FREE, NULL, ALL), (void)0);
		return ((void)0);
	}
	temp_v = ft_strjoin("=", value);
	if (!temp_v || garbagge(ADD, temp_v, ENV))
		return (garbagge(FREE, temp_v, ENV), (void)0);
	current->path = ft_strjoin(name_v, temp_v);
	if (!current->path || garbagge(ADD, current->path, ENV))
		return (garbagge(FREE, temp_v, ENV), (void)0);
}

char	*found_plus_modif_path(t_exp *new_upgrade_exp, char *value,
		char *modif_variable)
{
	char	*str_trim;
	char	*tmp1;

	str_trim = ft_strtrim(new_upgrade_exp->path, "\"");
	if (!str_trim || garbagge(ADD, str_trim, ENV))
		return ((garbagge(FLUSH, NULL, ALL)), NULL);
	value = ft_strjoin(str_trim, modif_variable);
	if (!value || garbagge(ADD, value, ENV))
		return (garbagge(FREE, NULL, ALL), NULL);
	tmp1 = ft_strjoin(value, "\"");
	if (!tmp1 || garbagge(ADD, tmp1, ENV))
		return (NULL);
	return (tmp1);
}

void	found_name_both_expo(char *modif_variable, char *value, char *name_v,
		t_exp *new_upgrade_exp)
{
	char	*tmp1;
	char	*tmp2;
	char	*good_path;

	tmp2 = NULL;
	good_path = ft_strjoin("export ", name_v);
	if (!good_path || garbagge(ADD, good_path, ENV))
		return ((void)0);
	if (modif_variable)
	{
		new_upgrade_exp->path = found_plus_modif_path(new_upgrade_exp, value,
				modif_variable);
		return ((void)0);
	}
	tmp1 = ft_strjoin(value, "\"");
	if (!tmp1 || garbagge(ADD, tmp1, ENV))
		return ((void)0);
	tmp2 = ft_strjoin("=\"", tmp1);
	if (!tmp2 || garbagge(ADD, tmp2, ENV))
		return (garbagge(FREE, tmp1, ENV), (void)0);
	new_upgrade_exp->path = ft_strjoin(good_path, tmp2);
	if (!new_upgrade_exp->path || garbagge(ADD, new_upgrade_exp->path, ENV))
		return (garbagge(FREE, tmp1, ENV), garbagge(FREE, tmp2, ENV), (void)0);
}

void	found_name_v_only_in_export(t_exp *new_upgrade_exp, char *name_v,
		char *value)
{
	char	*tmp1_deux;
	char	*tmp2_deux;
	char	*good_path;

	good_path = ft_strjoin("export ", name_v);
	if (!good_path || garbagge(ADD, good_path, ENV))
		return ((void)0);
	tmp1_deux = ft_strjoin(value, "\"");
	if (!tmp1_deux || garbagge(ADD, tmp1_deux, ENV))
		return ((void)0);
	tmp2_deux = ft_strjoin("=\"", tmp1_deux);
	if (!tmp2_deux || garbagge(ADD, tmp2_deux, ENV))
		return (garbagge(FREE, tmp1_deux, ENV), (void)0);
	new_upgrade_exp->path = ft_strjoin(good_path, tmp2_deux);
	if (!new_upgrade_exp->path || garbagge(ADD, new_upgrade_exp->path, ENV))
		return (garbagge(FREE, tmp1_deux, ENV), garbagge(FREE, tmp2_deux, ENV),
			(void)0);
}

void	add_environment_variable(t_envp **enviroment, char *name_v, char *value)
{
	t_envp	*new_variable;
	t_envp	*last;
	char	*equal_value;

	new_variable = (t_envp *)malloc(sizeof(t_envp));
	if (!new_variable || garbagge(ADD, new_variable, ENV))
		return (garbagge(FLUSH, NULL, ALL), (void)0);
	equal_value = ft_strjoin("=", value);
	if (!equal_value || garbagge(ADD, equal_value, ENV))
		return (garbagge(FLUSH, NULL, ALL), (void)0);
	new_variable->path = ft_strjoin(name_v, equal_value);
	if (!new_variable->path || garbagge(ADD, new_variable->path, ENV))
		return (garbagge(FLUSH, NULL, ALL), (void)0);
	new_variable->value = value;
	new_variable->name = name_v;
	new_variable->next = NULL;
	if (*enviroment == NULL)
		*enviroment = new_variable;
	else
	{
		last = *enviroment;
		while (last->next != NULL)
			last = last->next;
		last->next = new_variable;
	}
}
