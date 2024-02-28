/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:23:27 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:38:04 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*logic_print_variable(int i, t_envp *enviroment, t_cmd *arg_cmd,
		int e_st)
{
	char	*arg_value;

	arg_value = ft_strdup(arg_cmd->cmd);
	if (!arg_value || garbagge(ADD, arg_value, PARS))
		return (NULL);
	if (count_dollar(arg_value) > 0)
		return (ft_expand_value(arg_value, i, enviroment, e_st));
	return (NULL);
}

int	logic_print_echo(t_cmd *arg_cmd, int print_argument, char *expanded_value)
{
	(void)expanded_value;
	if (arg_cmd)
		print_argument = print_not_found(print_argument, arg_cmd);
	else
		print_argument = 1;
	return (print_argument);
}

int	found_echo_not_flag(t_cmd *arg_cmd)
{
	char	*expanded_value;
	int		print_argument;

	print_argument = 1;
	expanded_value = NULL;
	while (arg_cmd)
	{
		if (logic_display_error(arg_cmd))
			break ;
		if (ft_strcmp(arg_cmd->cmd, "$") == 0 && arg_cmd->next)
		{
			printf("%s ", arg_cmd->cmd);
			arg_cmd = arg_cmd->next;
		}
		print_argument = logic_print_echo(arg_cmd, print_argument,
				expanded_value);
		arg_cmd = arg_cmd->next;
	}
	printf("\n");
	return (0);
}

int	logic_print_echo_flag(t_cmd *to_pars, int error_status)
{
	t_cmd	*arg_cmd;

	arg_cmd = to_pars->next;
	if (!arg_cmd)
		return (printf("\n"), 1);
	error_status = found_echo_whit_flag(arg_cmd);
	return (error_status);
}

int	found_dollar_print_variable(t_cmd *to_pars, int error_status)
{
	t_cmd	*arg_cmd;

	while (to_pars)
	{
		if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo") == 0)
		{
			arg_cmd = to_pars->next;
			if (!arg_cmd)
				return (printf("\n"), 0);
			error_status = found_echo_not_flag(arg_cmd);
		}
		if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo -n") == 0)
			error_status = logic_print_echo_flag(to_pars, error_status);
		to_pars = to_pars->next;
	}
	return (error_status);
}