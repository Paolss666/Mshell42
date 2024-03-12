/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:03:10 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:05:41 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_cmd	*add_redirection_to_list(t_cmd **new_list_ptr, t_cmd *prev,
		t_cmd *current)
{
	t_cmd	*new_commande;

	new_commande = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_commande || garbagge(ADD, new_commande, PARS))
	{
		perror("malloc failure");
		return (NULL);
	}
	new_commande->cmd = ft_strdup(current->cmd);
	if (!new_commande->cmd || garbagge(ADD, new_commande->cmd, PARS))
	{
		garbagge(FREE, new_commande, PARS);
		return (NULL);
	}
	new_commande->next = NULL;
	if (prev != NULL)
		prev->next = new_commande;
	else
		*new_list_ptr = new_commande;
	return (new_commande);
}

t_cmd	*remove_redirections(t_cmd *to_pars)
{
	t_cmd	*new_list;
	t_cmd	*prev;
	t_cmd	*new_commande;
	t_cmd	*current;

	new_list = NULL;
	current = to_pars;
	prev = NULL;
	while (current)
	{
		if (!found_in_to_pars(current))
		{
			if (current->next != NULL && current->next->cmd != NULL)
				current = current->next->next;
			else
				current = current->next;
		}
		else
		{
			new_commande = add_redirection_to_list(&new_list, prev, current);
			prev = new_commande;
			current = current->next;
		}
	}
	return (new_list);
}

char	*check_redir_for_split(char *cmd)
{
	char		*result;
	t_for_re	*esp;

	esp = init_esp(cmd);
	result = (char *)malloc((esp->len + 2) * sizeof(char));
	if (!result || garbagge(ADD, result, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
	ft_strcpy(result, cmd, ft_strlen(cmd) + 1);
	while (result[++esp->i])
	{
		if (result[esp->i] == '<' || result[esp->i] == '>')
		{
			count_spaces_before_and_after(result, esp->i, esp);
			if (esp->spaces_before <= 3 && esp->spaces_after <= 3
				&& (result[esp->j_after_count] == '<'
					|| result[esp->j_after_count] == '>'))
			{
				ft_memmove(result + esp->i + 1,
					result + esp->i + 1 + esp->spaces_after,
					esp->len - esp->i - esp->spaces_after + 1);
				esp->len -= esp->spaces_after;
			}
		}
	}
	return (result);
}

void	add_spaces_around_token(char *token, char **new_token, char *last_char)
{
	if (*last_char != -1 && *last_char != ' ' && *last_char != '"'
		&& *last_char != '\'')
		*(*new_token)++ = ' ';
	*(*new_token)++ = *token;
	if ((*(token + 1) != ' ' && *(token + 1) != '\0' && *(token + 1) != '"'
			&& *(token + 1) != '\'') && (*token == '<' || *token == '>'
			|| *token == '|'))
		*(*new_token)++ = ' ';
	*last_char = *token;
}

char	*new_cmd_for_token(char *token)
{
	char	*new_com;

	new_com = (char *)malloc(ft_strlen(token) * 2 + 2);
	if (!new_com || garbagge(ADD, new_com, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
	return (new_com);
}