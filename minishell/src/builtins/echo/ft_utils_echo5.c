/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:17:12 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:24:17 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*find_next_non_n_token(const char *cmd)
{
	long unsigned int	idx;
	size_t				cmd_len;
	char				*result;

	idx = find_next_non_n_index(cmd);
	if (idx == 0)
		return (NULL);
	cmd_len = ft_strlen(cmd);
	result = malloc(cmd_len - idx + 1);
	if (!result || garbagge(ADD, result, PARS))
		return (NULL);
	if (result != NULL)
		ft_strcp_for_me(result, &cmd[idx]);
	return (result);
}

int	echo_flag_funny(t_cmd *to_pars, t_cmd *arg_cmd, int error_status)
{
	char	*str;

	str = find_next_non_n_token(to_pars->cmd);
	if (!str)
		error_status = logic_print_echo_flag(to_pars, error_status);
	else
	{
		printf("%s", str);
		arg_cmd = to_pars->next;
		error_status = found_echo_not_flag(arg_cmd);
	}
	return (error_status);
}

int	head_found_dollar_print_v(t_cmd *to_pars, int error_status, t_cmd *arg_cmd)
{
	if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo") == 0)
	{
		arg_cmd = to_pars->next;
		if (!arg_cmd)
			return (printf("\n"), 0);
		error_status = found_echo_not_flag(arg_cmd);
	}
	else if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo -n") == 0)
	{
		arg_cmd = to_pars->next;
		if (!arg_cmd)
			return (0);
		error_status = logic_print_echo_flag(to_pars, error_status);
	}
	else if (to_pars->cmd && ft_strncmp(to_pars->cmd, "echo -n",
			ft_strlen("echo -n")) == 0)
		error_status = echo_flag_funny(to_pars, arg_cmd, error_status);
	return (error_status);
}

int	found_dollar_print_variable(t_cmd *to_pars, int error_status, int c_pipe)
{
	t_cmd	*arg_cmd;

	arg_cmd = NULL;
	while (to_pars)
	{
		error_status = head_found_dollar_print_v(to_pars,
				error_status, arg_cmd);
		if (!c_pipe)
			return (error_status);
		to_pars = to_pars->next;
	}
	return (error_status);
}
