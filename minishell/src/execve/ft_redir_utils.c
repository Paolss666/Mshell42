/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 01:56:58 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:01:02 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	found_infile_or_endfile(t_cmd *to_pars)
{
	while (to_pars)
	{
		if (ft_strncmp(to_pars->cmd, "<", ft_strlen("<")) == 0)
			return (1);
		if (ft_strncmp(to_pars->cmd, ">", ft_strlen(">")) == 0)
			return (2);
		if (ft_strncmp(to_pars->cmd, ">>", ft_strlen(">>")) == 0)
			return (3);
		if (ft_strncmp(to_pars->cmd, "<<", ft_strlen("<<")) == 0)
			return (4);
		to_pars = to_pars->next;
	}
	return (0);
}

char	*direction_in_out_file(t_cmd *to_pars)
{
	while (to_pars)
	{
		if (ft_strcmp(to_pars->cmd, "<") == 0)
			return (to_pars->next->cmd);
		if (ft_strcmp(to_pars->cmd, ">") == 0)
			return (to_pars->next->cmd);
		if (ft_strcmp(to_pars->cmd, ">>") == 0)
			return (to_pars->next->cmd);
		if (ft_strcmp(to_pars->cmd, "<<") == 0)
			return (to_pars->next->cmd);
		to_pars = to_pars->next;
	}
	return (NULL);
}

void	append_to_list_red(t_cmd **new_list, t_cmd *cmd)
{
	t_cmd	*tail;

	tail = NULL;
	if (*new_list == NULL)
		*new_list = cmd;
	else
	{
		tail = *new_list;
		while (tail->next)
			tail = tail->next;
		tail->next = cmd;
	}
}

t_cmd	*add_cmd_for_redir(t_cmd *list)
{
	t_cmd	*new_list;
	int		i;
	char	**commande_split;
	t_cmd	*cmd;

	new_list = NULL;
	while (list != NULL)
	{
		i = -1;
		if (!list->cmd)
			return (NULL);
		commande_split = ft_split_garbage(list->cmd, ' ');
		if (!commande_split)
			return (NULL);
		while (commande_split[++i])
		{
			cmd = add_new_cmd(commande_split, i);
			if (!cmd)
				return (NULL);
			append_to_list_red(&new_list, cmd);
		}
		list = list->next;
	}
	return (new_list);
}

void	add_ep_redirection_and_pipes(t_cmd *head)
{
	t_cmd	*current;
	t_a_re	*add;

	add = add_init();
	current = head;
	while (current)
	{
		add->token = current->cmd;
		add->new_com = new_cmd_for_token(add->token);
		add->new_token = add->new_com;
		while (*add->token)
		{
			if (*add->token == '<' || *add->token == '>' || *add->token == '|')
				add_spaces_around_token(add->token,
					&add->new_token,
					&add->last_char);
			else
				*add->new_token++ = *add->token;
			add->last_char = *add->token;
			add->token++;
		}
		*add->new_token = '\0';
		current->cmd = check_redir_for_split(add->new_com);
		current = current->next;
	}
}