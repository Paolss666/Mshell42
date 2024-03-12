/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:31:30 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:49:09 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_v	*init_v(char *line, char *found_equal)
{
	int	len;
	t_v	*v;

	v = (t_v *)malloc(sizeof(t_v));
	if (!v || garbagge(ADD, v, ENV))
		return (NULL);
	len = found_equal - line;
	v->name = ft_substr(line, 0, len);
	if (!v->name || garbagge(ADD, v->name, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	v->value = ft_strdup(found_equal + 1);
	if (!v->value || garbagge(ADD, v->value, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), NULL);
	v->modif_variable = NULL;
	return (v);
}

void	update_environment_and_export(t_envp **enviroment, t_exp **export,
		char *line, char *found_equal)
{
	size_t	len;
	t_v		*v;
	char	*found_plus;

	v = init_v(line, found_equal);
	found_plus = ft_strchr(line, '+');
	if (found_plus)
	{
		v->modif_variable = ft_substr(found_plus, 2, ft_strlen(found_plus));
		if (!v->modif_variable || garbagge(ADD, v->modif_variable, ENV))
			return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), (void)0);
		len = ft_strlen(line) - ft_strlen(v->modif_variable) - 2;
		v->name = ft_substr(line, 0, len);
		if (!v->name || garbagge(ADD, v->name, ENV))
			return (garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE), (void)0);
	}
	logic_add_in_exp_env(enviroment, export, v, v->modif_variable);
}

void	udpate_plus_after_env_exp(t_envp **enviroment,
		t_exp **export, char *line, char *found_equal)
{
	size_t	len;
	t_v		*v;

	v = (t_v *)malloc(sizeof(t_v));
	if (!v || garbagge(ADD, v, ENV))
		return ((void)0);
	len = found_equal - line;
	v->name = ft_substr(line, 0, len);
	if (!v->name || garbagge(ADD, v->name, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), (void)0);
	v->value = ft_strdup(found_equal + 1);
	if (!v->value || garbagge(ADD, v->value, ENV))
		return (garbagge(FREE, NULL, ALL), exit(EXIT_FAILURE), (void)0);
	v->modif_variable = NULL;
	logic_add_in_exp_env(enviroment, export, v, v->modif_variable);
}

int	is_valid_export_value(char *cmd)
{
	int	equal_found;
	int	plus_count;

	if (!cmd || *cmd == '\0')
		return (1);
	equal_found = 0;
	plus_count = 0;
	while (*cmd != '\0')
	{
		if (*cmd == '=')
		{
			if (plus_count > 1)
				return (1);
			equal_found = 1;
		}
		else if (*cmd == '+')
			plus_count++;
		else if (!equal_found && !ft_isalnum(*cmd))
			return (1);
		cmd++;
	}
	return (0);
}

void	remove_q(char *s)
{
	char	*p;
	char	*q;

	p = s;
	q = s;
	while (*p != '\0')
	{
		if (*p != '"' && *p != '\'')
		{
			*q = *p;
			q++;
		}
		p++;
	}
	*q = '\0';
}
