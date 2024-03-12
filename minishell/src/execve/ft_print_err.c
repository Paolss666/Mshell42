/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:57:12 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:58:06 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_for_logic_err(t_execve *pipex, t_cmd *to_pars, char **cmd)
{
	if (!to_pars->cmd)
	{
		ft_error_commande_split(cmd[0]);
		pipex->error = 127;
		return (pipex->error);
	}
	else if (to_pars->cmd && ft_strchr(to_pars->cmd, '\"'))
	{
		ft_error_quotes(pipex, cmd[0]);
		return (pipex->error);
	}
	else if (to_pars->cmd && ft_strchr(to_pars->cmd, '\''))
	{
		ft_error_single_quotes(pipex, cmd[0]);
		return (pipex->error);
	}
	pipex->error = logic_split_for_commande(cmd[0], pipex);
	return (pipex->error);
}

int	ft_error_commande_not_to_pars(t_cmd *to_pars, t_execve *pipex)
{
	char	**cmd;

	pipex->error = 127;
	cmd = ft_split_garbage_gogo(to_pars->cmd, ' ');
	if (!cmd)
		return (garbagge(FLUSH, NULL, ALL), exit(99), 0);
	if (ft_strcmp(to_pars->cmd, " ") == 0)
	{
		ft_putstr_fd("bash : ", 2);
		ft_putstr_fd(to_pars->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		pipex->error = 127;
		return (pipex->error);
	}
	pipex->error = check_for_logic_err(pipex, to_pars, cmd);
	return (pipex->error);
}
