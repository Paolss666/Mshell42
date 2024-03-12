/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redir3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:07:23 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:08:45 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	found_quotes(t_cmd *to_pars)
{
	char	*trimmed;
	char	*cmd;

	while (to_pars)
	{
		cmd = to_pars->cmd;
		trimmed = ft_strtrim(cmd, "\"");
		if (!trimmed || garbagge(ADD, trimmed, EX))
			return ((void)0);
		to_pars->cmd = trimmed;
		to_pars = to_pars->next;
	}
}

void	found_single_quotes(t_cmd *to_pars)
{
	char	*trimmed;
	char	*cmd;

	while (to_pars)
	{
		cmd = to_pars->cmd;
		trimmed = ft_strtrim(cmd, "\'");
		if (!trimmed || garbagge(ADD, trimmed, EX))
			return ((void)0);
		to_pars->cmd = trimmed;
		to_pars = to_pars->next;
	}
}

void	add_node_sp(t_cmd **head_ref, char *cmd)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->cmd = cmd;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

void	count_spaces_before_and_after(char *str, int index, t_for_re *re)
{
	int	j;

	re->spaces_before = 0;
	re->spaces_after = 0;
	re->j_after_count = index + 1;
	j = index - 1;
	while (j >= 0 && str[j] == ' ')
	{
		(re->spaces_before)++;
		j--;
	}
	j = index + 1;
	while (str[j] == ' ')
	{
		(re->spaces_after)++;
		j++;
	}
	re->j_after_count = j;
}

t_for_re	*init_esp(char *cmd)
{
	t_for_re	*esp;

	esp = (t_for_re *)malloc(sizeof(t_for_re));
	if (!esp || garbagge(ADD, esp, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	esp->len = ft_strlen(cmd);
	esp->j_after_count = 0;
	esp->spaces_after = 0;
	esp->spaces_before = 0;
	esp->i = -1;
	return (esp);
}