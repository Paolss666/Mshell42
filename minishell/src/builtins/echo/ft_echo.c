/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:37 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:12:16 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal_received;

int	print_not_found(int print_argument, t_cmd *arg_cmd)
{
	if (print_argument && arg_cmd->cmd != NULL && arg_cmd->cmd[0] != '\0')
	{
		remove_quote(arg_cmd->cmd);
		printf("%s", arg_cmd->cmd);
		if (arg_cmd->next)
			printf(" ");
		return (print_argument);
	}
	else
		print_argument = 1;
	return (print_argument);
}

int	logic_display_error(t_cmd *arg_cmd)
{
	char	*cmd;
	size_t	count;

	if (ft_strcmp(arg_cmd->cmd, "|") == 0 || ft_strcmp(arg_cmd->cmd, "<") == 0
		|| ft_strcmp(arg_cmd->cmd, ">>") == 0 || ft_strcmp(arg_cmd->cmd,
			">") == 0 || ft_strcmp(arg_cmd->cmd, "<<") == 0)
		return (1);
	if (ft_strcmp(arg_cmd->cmd, "$") == 0 && !arg_cmd->next)
	{
		printf("%s", arg_cmd->cmd);
		return (1);
	}
	if (arg_cmd->cmd && arg_cmd->cmd[0] && !check_if_only_space(arg_cmd->cmd)
		&& !arg_cmd->next)
	{
		count = ft_strl(arg_cmd->cmd);
		cmd = malloc(count + 1);
		if (garbagge(ADD, cmd, PARS))
			(garbagge(FLUSH, NULL, ALL), exit(99));
		ft_strlcpy_msh(cmd, arg_cmd->cmd, count + 1, NULL);
		printf("%s", cmd);
		return (1);
	}
	return (0);
}

int	found_echo_whit_flag(t_cmd *arg_cmd)
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
			printf("%s", arg_cmd->cmd);
			arg_cmd = arg_cmd->next;
		}
		print_argument = logic_print_echo(arg_cmd, print_argument,
				expanded_value);
		arg_cmd = arg_cmd->next;
	}
	return (0);
}

char	*creation_var_name(int start, int i, char *arg_value)
{
	char	*var_name;
	size_t	len;

	len = 0;
	if (!arg_value)
		return (NULL);
	while (arg_value[i] && (valid_variable_char(arg_value[i])))
		i++;
	len = i - start;
	var_name = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_name || garbagge(ADD, var_name, ENV))
		return (NULL);
	ft_strlcpy(var_name, arg_value + start, len + 1);
	return (var_name);
}

char	*add_logic_garbage(char *var_value, char *found)
{
	char	*value_found;

	if (!found || !var_value)
		return (NULL);
	value_found = ft_strjoin(var_value, found);
	if (!value_found || garbagge(ADD, value_found, ENV))
		return (NULL);
	garbagge(FREE, var_value, PARS);
	garbagge(FREE, found, PARS);
	return (value_found);
}
