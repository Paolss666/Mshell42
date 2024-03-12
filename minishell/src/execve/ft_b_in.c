/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_b_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:16:31 by npoalett          #+#    #+#             */
/*   Updated: 2024/03/12 02:17:37 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	found_echo_in_pipe(t_cmd *new_to_pars)
{
	char	*echo;

	echo = ft_substr(new_to_pars->cmd, 5, ft_strlen(new_to_pars->cmd));
	if (!echo || garbagge(ADD, echo, PARS))
		return (garbagge(FLUSH, NULL, ALL), exit(1));
	remove_quote(echo);
	printf("%s\n", echo);
	if (new_to_pars->next)
		printf(" ");
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}

void	found_echo_in_pipe_flag(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (ft_check_valid_flag_echo(tmp[i]))
			break ;
		i++;
	}
	while (tmp[i])
	{
		printf("%s", tmp[i]);
		if (tmp[i + 1])
			printf(" ");
		i++;
	}
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}

void	print_env_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array == NULL)
		return ;
	while (str_array[i])
	{
		printf("%s\n", str_array[i]);
		i++;
	}
}

const char	*found_in_env_char(char **envi)
{
	int			i;
	const char	*f;

	i = -1;
	while (envi[++i])
	{
		f = ft_strnstr(envi[i], "PWD=", ft_strlen("PWD="));
		if (f)
			return (f);
	}
	return (NULL);
}

void	found_pwd_in_pipe(t_execve *pipex)
{
	const char	*pwd;

	pwd = found_in_env_char(pipex->new_enviroment);
	printf("%s\n", pwd);
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}