/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:09:47 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:15:45 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_a_re	*add_init(void)
{
	t_a_re	*add;

	add = (t_a_re *)malloc(sizeof(t_a_re));
	if (!add || garbagge(ADD, add, PARS))
		((garbagge(FLUSH, NULL, ALL), exit(99)));
	add->last_char = -1;
	add->new_com = NULL;
	add->new_token = NULL;
	add->token = NULL;
	return (add);
}

t_cmd	*parsing_before_pipe_red(t_cmd *to_pars)
{
	t_cmd	*cur;

	cur = to_pars;
	add_ep_redirection_and_pipes(cur);
	cur = add_cmd_for_redir(cur);
	return (cur);
}

t_cmd	*copy_node(t_cmd *original)
{
	t_cmd	*copy;

	if (!original)
		return (NULL);
	copy = (t_cmd *)malloc(sizeof(t_cmd));
	if (!copy || garbagge(ADD, copy, PARS))
		return (NULL);
	copy->cmd = original->cmd;
	copy->next = copy_node(original->next);
	return (copy);
}

char	*create_temp_buffer(const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*temp;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	total_len = len1 + len2 + 2;
	temp = (char *)malloc(total_len * sizeof(char));
	if (!temp || garbagge(ADD, temp, PARS))
		return (NULL);
	ft_strlcpy(temp, str1, total_len);
	ft_strlcat(temp, " ", total_len);
	ft_strlcat(temp, str2, total_len);
	return (temp);
}

void	creation_cmd(t_cmd **current_commande, const char *new_cmd)
{
	t_cmd	*new_node;
	char	*temp;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node || garbagge(ADD, new_node, PARS))
		return (perror("Memory allocation error"), exit(EXIT_FAILURE), (void)0);
	new_node->cmd = ft_strdup(new_cmd);
	if (!new_node->cmd || garbagge(ADD, new_node->cmd, PARS))
		return (garbagge(FREE, new_node, PARS), (void)0);
	new_node->next = NULL;
	if (*current_commande == NULL)
		*current_commande = new_node;
	else
	{
		temp = create_temp_buffer((*current_commande)->cmd, new_node->cmd);
		garbagge(FREE, (*current_commande)->cmd, PARS);
		garbagge(FREE, *current_commande, PARS);
		*current_commande = (t_cmd *)malloc(sizeof(t_cmd));
		if (!(*current_commande) || garbagge(ADD, *current_commande, PARS))
			return (perror("Memory allocation error"), exit(EXIT_FAILURE),
				(void)0);
		(*current_commande)->cmd = temp;
		(*current_commande)->next = NULL;
	}
}