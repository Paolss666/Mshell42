/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commandes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:11:47 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 03:11:44 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*display_prompt(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(COLOR_RED "Mshell$ " RESET_COLOR);
		if (!line || garbagge(ADD, line, PARS))
			return (NULL);
		if (!line[0])
		{
			garbagge(FREE, line, PARS);
			line = NULL;
			continue ;
		}
		if (line)
			add_history(line);
		return (line);
	}
}

int	ft_found_pwd(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "pwd") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

int	minishell_brain_bis(t_cmd *to_pars, t_envp *enviroment, t_exp *export,
		int error_status)
{
	int	c_pipe;

	c_pipe = found_count_pipe(to_pars);
	if (!found_count_pipe(to_pars) && found_echo(to_pars)
		&& !found_infile_or_endfile(to_pars))
	{
		found_echo(to_pars);
		error_status = found_dollar_print_variable(to_pars, error_status,
				c_pipe);
	}
	else if (!found_token(to_pars) && !found_infile_or_endfile(to_pars))
		error_status = ft_execve(to_pars, enviroment, export, error_status);
	else
		error_status = ft_execve(to_pars, enviroment, export, error_status);
	return (error_status);
}

t_brain	*init_brain(void)
{
	t_brain	*brain;

	brain = (t_brain *)malloc(sizeof(t_brain));
	if (!brain || garbagge(ADD, brain, ENV))
		(perror(" "), exit(130));
	brain->enviroment = NULL;
	brain->export = NULL;
	brain->line = NULL;
	brain->error = 0;
	brain->to_pars = NULL;
	return (brain);
}
