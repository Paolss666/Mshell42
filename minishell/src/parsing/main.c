/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:24:45 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 03:04:19 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		g_signal_received = 0;


int	minishell_brain(t_cmd *to_pars, t_envp **enviroment, t_exp **export,
		int error_status)
{
	to_pars = expand_dollar(&to_pars, *enviroment, error_status);
	if (!found_count_pipe(to_pars) && ft_found_pwd(to_pars))
		return (ft_pwd(to_pars), error_status);
	if (!found_count_pipe(to_pars) && found_unset(to_pars))
		return (unset_delete_variable(to_pars, enviroment, export),
			error_status);
	if (!found_count_pipe(to_pars) && !found_infile_or_endfile(to_pars)
		&& to_pars && !to_pars->next && found_export(to_pars))
		return (print_export_list(*export), error_status);
	if (!found_count_pipe(to_pars) && ft_envp(to_pars) == 2)
		return (print_list_envp(*enviroment), error_status);
	if (!found_count_pipe(to_pars) && to_pars->next && found_export(to_pars))
		return (add_export_env(to_pars, enviroment, export));
	if (!found_count_pipe(to_pars) && found_exit(to_pars))
		return (ft_exit(to_pars, *enviroment, *export));
	if (!found_count_pipe(to_pars) && ft_cd(to_pars))
		return (found_cd_pwd_update(to_pars, *enviroment, *export));
	return (minishell_brain_bis(to_pars, *enviroment, *export, error_status));
}

int	main_brain(char **env, t_brain *brain)
{
	if (brain->error == 999)
		brain->error = 0;
	brain->prev_err = brain->error;
	if (!brain->to_pars && brain->line)
		brain->to_pars = add_cmd_star(brain->to_pars, brain->line);
	if (brain->to_pars)
		join_found_flag(&brain->to_pars);
	if (!brain->enviroment)
		brain->enviroment = found_and_add_env(env, brain->enviroment);
	if (!brain->export)
		brain->export = add_env_with_export(brain->enviroment);
	if (brain->export)
		export_env_sort(brain->export);
	brain->error = minishell_brain(brain->to_pars, &brain->enviroment,
			&brain->export, brain->prev_err);
	return (brain->error);
}

void	ft_update_exit_code(int *error)
{
	if (g_signal_received)
	{
		if (g_signal_received == 60)
			*error = 130;
		if (g_signal_received == 59)
			*error = 130;
		if (g_signal_received == 127)
			*error = 127;
		g_signal_received = 0;
	}
}

void	head_minishell(char **env, int temp_error, t_brain *brain)
{
	set_signal_action(1);
	brain->line = display_prompt();
	if (!brain->line)
		(garbagge(FLUSH, NULL, ALL), printf("exit\n"), exit(130));
	if (brain->error)
		temp_error = brain->error;
	brain->error = error_manager(brain->line);
	if (!brain->error || g_signal_received)
	{
		brain->error = temp_error;
		temp_error = 0;
		ft_update_exit_code(&brain->error);
		if (!ft_check_only_quote(brain->line))
		{
			ft_putstr_fd("bash: : command not found\n", 2);
			brain->error = 127;
		}
		else
			brain->error = main_brain(env, brain);
	}
	if (brain->to_pars)
		brain->to_pars = free_cmds_list(brain->to_pars);
}

int	main(int ac, char **av, char **env)
{
	int		temp_error;
	t_brain	*brain;

	((void)av, (void)ac);
	brain = init_brain();
	if (!brain)
		return (124);
	g_signal_received = 0;
	temp_error = 0;
	if (ac != 1)
		return (ft_putstr_fd("Don't need arguments\n", 2), garbagge(FLUSH, NULL,
				ALL), 1);
	ft_issatty(brain, env);
	while (1)
		head_minishell(env, temp_error, brain);
	if (brain->enviroment || brain->export)
		garbagge(FLUSH, NULL, ALL);
	return (0);
}