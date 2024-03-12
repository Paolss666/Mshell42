/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:52:41 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:48:55 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exp	*add_env_with_export(t_envp *enviroment)
{
	t_exp	*export_list;
	t_exp	*current_export;
	t_exp	*new_export;

	export_list = NULL;
	current_export = NULL;
	if (!enviroment)
		return (NULL);
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

int	handle_export_error(char *cmd)
{
	ft_putstr_fd("export : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" not a valid identifier\n", 2);
	return (1);
}
