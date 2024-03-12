/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:45:43 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:48:29 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export_logic( t_envp **enviroment, t_exp **export, char *line)
{
	char	*found_equal;
	char	*found_plus_aft;
	t_exp	*check_equal_list;

	found_plus_aft = NULL;
	found_equal = ft_strchr(line, '=');
	if (found_equal)
		found_plus_aft = ft_strchr(found_equal, '+');
	check_equal_list = *export;
	if (found_equal && (ft_strchr(found_equal, '\'')
			|| ft_strchr(found_equal, '\"')))
		remove_q(found_equal);
	if ((line && found_equal && !found_plus_aft))
		update_environment_and_export(enviroment, export, line,
			found_equal);
	else if ((line && found_equal && found_plus_aft))
		udpate_plus_after_env_exp(enviroment, export, line, found_equal);
	else
		add_export_variable_pro(line, found_equal, export,
			check_equal_list);
}

int	check_plus_before(char *line)
{
	char	*pr;

	pr = NULL;
	if (!line)
		return (1);
	pr = ft_strchr(line, '+');
	if (pr && pr[1] != '=')
		return (1);
	return (0);
}

int	add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export)
{
	char	*line;
	int		err;

	err = 0;
	while (to_pars->next)
	{
		if (!valid_variable_char(to_pars->next->cmd[0])
			|| check_plus_before(to_pars->next->cmd))
		{
			err = handle_export_error(to_pars->next->cmd);
			if (!to_pars->next->next)
				return (err);
			line = to_pars->next->next->cmd;
		}
		else
			line = to_pars->next->cmd;
		if (is_valid_export_value(line))
		{
			err = handle_export_error(line);
			return (err);
		}
		ft_export_logic(enviroment, export, line);
		to_pars = to_pars->next;
	}
	return (0);
}
