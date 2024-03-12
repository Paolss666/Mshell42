/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_check_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:46:35 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:49:02 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*return_exec(char *exec, char **with_flag, char **env_split)
{
	if (access(exec, F_OK | X_OK) == 0)
		return (ft_free_tab_garbage(with_flag), ft_free_tab_garbage(env_split),
			exec);
	return (NULL);
}

char	*check_path_absolut(char **with_flag, t_execve *pipex, int *dir)
{
	if (is_directory(with_flag[0]))
		return (*dir = 1, NULL);
	if (access(with_flag[0], F_OK | X_OK) == 0)
		return (with_flag[0]);
	if (access(with_flag[0], F_OK | X_OK) == -1)
	{
		(void)pipex;
		return (NULL);
	}
	return (NULL);
}

void	f_gbgb(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		garbagge(FREE, tab[i], PARS);
	garbagge(FREE, tab, PARS);
}

void	ft_init_var_0(int *i, int *dir)
{
	*i = -1;
	*dir = 0;
}

char	*logic_get_good_path(char **with_flag, char **env_split,
		t_execve *pipex)
{
	char	*exec;
	char	*try_line;
	int		i;
	int		dir;

	ft_init_var_0(&i, &dir);
	if (check_path_absolut(with_flag, pipex, &dir))
		return (with_flag[0]);
	if (dir == 1)
		return (NULL);
	while (env_split[++i])
	{
		try_line = ft_strjoin(env_split[i], "/");
		if (!try_line || garbagge(ADD, try_line, ENV))
			return (f_gbgb(with_flag), f_gbgb(env_split), NULL);
		exec = ft_strjoin(try_line, with_flag[0]);
		if (!exec || garbagge(ADD, exec, ENV))
			return (NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (f_gbgb(with_flag), f_gbgb(env_split), exec);
		if (access(exec, F_OK | X_OK) == -1 && pipex)
			pipex->error = 0;
		garbagge(FREE, exec, ENV);
	}
	return (NULL);
}