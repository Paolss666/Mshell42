/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:52:41 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:47:43 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE EXPORT */

int	found_export(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "export") == 0)
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
		return (perror("ERROR: t_exp"), exit(EXIT_FAILURE), NULL);
	new_export->path = modif_path_for_export(enviroment);
	if (!new_export || garbagge(ADD, new_export->path, ENV))
		return (NULL);
	new_export->path = ft_strjoin(new_export->path, "\"");
	if (!new_export->path || garbagge(ADD, new_export->path, ENV))
		return (NULL);
	new_export->name = NULL;
	new_export->value = ft_strdup(ft_strchr(new_export->path, '='));
	if (!new_export->value || garbagge(ADD, new_export->value, ENV))
		return (garbagge(FREE, new_export->path, ENV), exit(EXIT_FAILURE),
			NULL);
	new_export->next = NULL;
	return (new_export);
}

/// ajoute export avec env et je le modif export variable="value" //
t_exp	*add_env_with_export(t_envp *enviroment)
{
	t_exp	*export_list;
	t_exp	*current_export;
	t_exp	*new_export;

	export_list = NULL;
	current_export = NULL;
	while (enviroment != NULL)
	{
		new_export = init_export(enviroment);
		if (export_list == NULL)
		{
			export_list = new_export;
			current_export = export_list;
		}
		else
		{
			current_export->next = new_export;
			current_export = new_export;
		}
		enviroment = enviroment->next;
	}
	return (export_list);
}

void	print_export_list(t_exp *export)
{
	while (export != NULL)
	{
		printf("%s\n", export->path);
		export = export->next;
	}
}

t_envp	*logic_init_node(t_envp *new_node, const char *name, const char *value,
		char *temp)
{
	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node || garbagge(ADD, new_node, ENV))
		return (perror("Memory allocation failed"), NULL);
	new_node->name = ft_strdup(name);
	if (!new_node->name || garbagge(ADD, new_node->name, ENV))
		return (garbagge(FREE, new_node, ENV), NULL);
	new_node->value = ft_strdup(value);
	if (!new_node->value || garbagge(ADD, new_node->value, ENV))
		return (garbagge(FREE, new_node->name, ENV), garbagge(FREE, new_node,
				ENV), NULL);
	temp = ft_strjoin("=", value);
	if (!temp || garbagge(ADD, temp, ENV))
		return (garbagge(FREE, new_node->value, ENV), garbagge(FREE,
				new_node->name, ENV), garbagge(FREE, new_node, ENV), NULL);
	new_node->path = ft_strjoin(name, temp);
	if (!new_node->path || garbagge(ADD, new_node->path, ENV))
		return (garbagge(FREE, new_node->value, ENV), garbagge(FREE,
				new_node->name, ENV), garbagge(FREE, new_node, ENV), NULL);
	new_node->next = NULL;
	return (new_node);
}

t_envp	*add_node_to_end(t_envp **list, const char *name, const char *value)
{
	t_envp	*new_node;
	t_envp	*current;
	char	*temp;

	temp = NULL;
	new_node = NULL;
	new_node = logic_init_node(new_node, name, value, temp);
	if (*list == NULL)
	{
		*list = new_node;
		return (*list);
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (*list);
}

void	handle_export_error(char *cmd)
{
	ft_putstr_fd("export : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" identifiant non variable\n", 2);
}

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


void	udpate_plus_after_env_exp(t_envp **enviroment, t_exp **export, char *line, char *found_equal)
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


int is_valid_export_value(char *cmd)
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

void remove_q(char *s)
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

void	ft_export_logic( t_envp **enviroment, t_exp **export, char *line)
{
	char	*found_equal;
	char	*found_plus_aft;
	t_exp	*check_equal_list;

	found_plus_aft = NULL;
	found_equal = ft_strchr(line, '=');
	if (found_equal)
		found_plus_aft = ft_strchr(found_equal, '+');
	check_equal_list = *export;
	if (found_equal && (ft_strchr(found_equal, '\'')
			|| ft_strchr(found_equal, '\"')))
		remove_q(found_equal);
	if ((line && found_equal && !found_plus_aft))
		update_environment_and_export(enviroment, export, line,
			found_equal);
	else if ((line && found_equal && found_plus_aft))
		udpate_plus_after_env_exp(enviroment, export, line, found_equal);
	else
		add_export_variable_pro(line, found_equal, export,
			check_equal_list);
}

int	add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export)
{
	char	*line;

	while (to_pars->next)
	{
		if (!valid_variable_char(to_pars->next->cmd[0]))
		{
			handle_export_error(to_pars->cmd);
			if (!to_pars->next->next)
				return (1);
			line = to_pars->next->next->cmd;
		}
		else
			line = to_pars->next->cmd;
		if (is_valid_export_value(line))
		{
			handle_export_error(line);
			return (1);
		}
		ft_export_logic(enviroment, export, line);
		to_pars = to_pars->next;
	}
	return (0);
}
