/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_for_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:41:28 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:46:00 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_cmd	*add_new_cmd(char **commande_split, int i)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd || garbagge(ADD, cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	cmd->cmd = ft_strdup(commande_split[i]);
	if (!cmd->cmd || garbagge(ADD, cmd->cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	cmd->count = 0;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*add_cmd_star(t_cmd *list, char *line)
{
	t_cmd	*cmd;
	t_cmd	*current;
	int		i;
	char	**commande_split;

	i = -1;
	if (!line)
		return (NULL);
	commande_split = ft_split_garbage(line, '\v');
	if (!commande_split)
		return (ft_free_tab_garbage(commande_split), NULL);
	while (commande_split[++i])
	{
		cmd = add_new_cmd(commande_split, i);
		if (!list)
			list = cmd;
		else
		{
			current = list;
			while (current->next)
				current = current->next;
			current->next = cmd;
		}
	}
	return (list);
}

t_cmd	*add_cmd_list(t_cmd *list, char **commande_split, char *line)
{
	t_cmd	*cmd;
	t_cmd	*current;
	int		i;

	i = -1;
	if (!commande_split)
	{
		commande_split = ft_split_garbage(line, ' ');
		if (!commande_split)
			return (ft_free_tab_garbage(commande_split), NULL);
	}
	while (commande_split[++i])
	{
		cmd = add_new_cmd(commande_split, i);
		if (!list)
			list = cmd;
		else
		{
			current = list;
			while (current->next)
				current = current->next;
			current->next = cmd;
		}
	}
	return (list);
}

void	change_in_exp(t_exp *export)
{
	int		n;
	char	*temp;
	char	*temp1;
	char	*final;

	export->value = ft_strchr(export->path, '=') + 1;
	export->name = ft_strdup("export SHLVL=\"");
	if (!export->name || garbagge(ADD, export->name, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	temp1 = ft_strtrim(export->value, "\"");
	if (!temp1 || garbagge(ADD, temp1, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	n = ft_atoi(temp1) + 1;
	temp = ft_itoa(n);
	if (!temp || garbagge(ADD, temp, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	final = ft_strjoin(temp, "\"");
	if (!final || garbagge(ADD, final, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	export->path = ft_strjoin(export->name, final);
	if (!export->path || garbagge(ADD, export->path, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
}

int    ft_check_only_quote(char *line)
{
    int        i;
    t_quote    q;

    i = 0;
    q.d_q = 0;
    q.s_q = 0;
    while (line[i])
    {
        ft_inc_quote(line[i], &q.d_q, &q.s_q);
        if ((line[i] != '\'' && line[i] != '"')
			|| ((q.d_q % 2 == 1 && q.s_q % 2 == 0 && line[i] == '\'')
			|| (q.s_q % 2 == 1 && q.d_q % 2 == 0 && line[i] == '"')))
            return (1);
        i++;
    }
    if (q.d_q % 2 == 0 && q.s_q % 2 == 0)
        return (0);
    return (1);
}