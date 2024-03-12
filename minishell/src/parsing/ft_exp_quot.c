/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_quot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:54:29 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:55:57 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	process_token(const char *start, const char *end, char *tokens[],
		int *i)
{
	size_t	len;

	tokens[*i] = ft_strndup_g(start, end - start);
	if (!tokens[*i])
		(garbagge(FLUSH, NULL, ALL), exit(99));
	len = ft_strlen(tokens[*i]);
	tokens[*i][len] = *end;
	tokens[*i][len + 1] = '\0';
	(*i)++;
}

char	*logic_sgl_q(char *joined, char *split)
{
	if (joined)
	{
		joined = ft_strjoin(joined, split);
		if ((!joined || garbagge(ADD, joined, PARS)))
			(garbagge(FLUSH, NULL, ALL), exit(99));
	}
	else
	{
		joined = ft_strdup(split);
		if ((!joined || garbagge(ADD, joined, PARS)))
			(garbagge(FLUSH, NULL, ALL), exit(99));
	}
	return (joined);
}

char	*ft_found_all_qo(char **split, int r_st, t_envp *env)
{
	char	*joined;
	int		j;

	j = 0;
	joined = NULL;
	while (split[j])
	{
		if (j == 0)
		{
			if (joined)
			{
				joined = ft_strjoin(joined, ft_expand_value(split[j], 1, env,
							r_st));
				if ((!joined || garbagge(ADD, joined, PARS)))
					(garbagge(FLUSH, NULL, ALL), exit(99));
			}
			else
				joined = ft_expand_value(split[j], 1, env, r_st);
		}
		else
			joined = logic_sgl_q(joined, split[j]);
		j++;
	}
	return (joined);
}

char	*exp_in_all_quotes(t_cmd *current, t_envp *environment, int r_st)
{
	char	*cmd;
	char	**split;

	split = ft_split_garbage_gogo_quote(current->cmd, ' ');
	cmd = ft_found_all_qo(split, r_st, environment);
	garbagge(FREE, current->cmd, PARS);
	return (cmd);
}

void	logic_exp_quotes(int r_st, int i, t_envp *environment, t_cmd *current)
{
	if (logic_check_type_quotes(current->cmd) == 4
		|| logic_check_type_quotes(current->cmd) == 2)
		current->cmd = exp_in_all_quotes(current, environment, r_st);
	if (logic_check_type_quotes(current->cmd) == 3)
	{
		if (current->cmd && ft_strchr(current->cmd, '$'))
			logic_expand_variable(i, environment, current, r_st);
	}
	else if (logic_check_type_quotes(current->cmd) == 0)
	{
		if (current->cmd && !ft_strcmp(current->cmd, "$?"))
			logic_found_dollar_interrogation(current, r_st);
		if (current->cmd && ft_strchr(current->cmd, '$'))
			logic_expand_variable(i, environment, current, r_st);
	}
}
