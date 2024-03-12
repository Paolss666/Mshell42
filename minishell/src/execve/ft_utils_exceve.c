/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exceve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:54:31 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 01:02:00 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	add_command_to_list_token(t_cmd **command_list, t_cmd *command)
{
	t_cmd	*temp_list;

	if (!*command_list)
		*command_list = command;
	else
	{
		temp_list = *command_list;
		while (temp_list->next)
			temp_list = temp_list->next;
		temp_list->next = command;
	}
}

void	handle_pipe_case(t_cmd *temp, t_cmd *prev_temp, t_cmd *command_list)
{
	t_cmd	*next_temp;
	t_cmd	*empty_command;

	next_temp = temp->next;
	if (!prev_temp || (prev_temp && ft_strcmp(temp->cmd, "|") == 0
			&& ft_strcmp(prev_temp->cmd, "|") == 0))
	{
		empty_command = NULL;
		creation_cmd_empty(&empty_command, NULL);
		add_command_to_list_token(&command_list, empty_command);
	}
	if (!next_temp)
	{
		empty_command = NULL;
		creation_cmd_empty(&empty_command, NULL);
		add_command_to_list_token(&command_list, empty_command);
	}
}

t_cmd	*loop_p_for_token(t_cmd *command_list, t_cmd *temp, t_cmd *prev_temp,
		t_cmd *current_command)
{
	while (temp)
	{
		if (ft_strcmp(temp->cmd, "|") != 0 && temp->cmd)
		{
			creation_cmd(&current_command, temp->cmd);
			prev_temp = temp;
			temp = temp->next;
			if (!temp || (temp && ft_strcmp(temp->cmd, "|") == 0))
			{
				add_command_to_list_token(&command_list, current_command);
				current_command = NULL;
			}
			continue ;
		}
		else
			handle_pipe_case(temp, prev_temp, command_list);
		prev_temp = temp;
		temp = temp->next;
	}
	return (command_list);
}

t_cmd	*parse_for_token(t_cmd *to_pars)
{
	t_cmd	*command_list;
	t_cmd	*temp;
	t_cmd	*prev_temp;
	t_cmd	*current_command;

	temp = to_pars;
	command_list = NULL;
	prev_temp = NULL;
	current_command = NULL;
	command_list = loop_p_for_token(command_list,
			temp,
			prev_temp,
			current_command);
	return (command_list);
}
