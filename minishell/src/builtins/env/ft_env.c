/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:27:26 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 12:49:48 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (NULL);
	while (src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_envp	*create_enviroment(char **env, int i)
{
	int		len;
	t_envp	*current;
	char	*shlvl;

	len = 0;
	current = (t_envp *)malloc(sizeof(t_envp));
	if (!current || garbagge(ADD, current, ENV))
		return (garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE), NULL);
	shlvl = found_shlvl_init(env[i]);
	if (shlvl)
		env[i] = shlvl;
	current->path = env[i];
	current->value = ft_strdup(ft_strchr(current->path, '=') + 1);
	if (!current->value || garbagge(ADD, current->value, ENV))
		return (garbagge(FREE, current->path, ENV), NULL);
	len = ft_strlen(current->path) - ft_strlen(current->value);
	current->name = ft_substr(current->path, 0, len - 1);
	if (!current->name || garbagge(ADD, current->name, ENV))
		return (garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE), NULL);
	current->next = NULL;
	return (current);
}

char	**creation_env(void)
{
	char	*pwd;
	char	**env;

	env = (char **)malloc(sizeof(char *) * 4);
	if (!env || garbagge(ADD, env, PARS))
		return (NULL);
	pwd = getcwd(NULL, 0);
	garbagge(ADD, pwd, ENV);
	env[0] = ft_strjoin("PWD=", pwd);
	if (!env[0] || garbagge(ADD, env[0], ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	env[1] = ft_strdup("SHLVL=0");
	if (!env[1] || garbagge(ADD, env[1], ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	env[2] = ft_strdup("_=/usr/bin/");
	if (!env[2] || garbagge(ADD, env[2], ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	env[3] = NULL;
	return (env);
}

t_envp	*found_and_add_env(char **env, t_envp *enviroment)
{
	t_envp	*current;
	t_envp	*envp;
	int		i;

	i = -1;
	current = NULL;
	if (!env || env[0] == NULL)
		env = creation_env();
	while (env && env[++i])
	{
		current = create_enviroment(env, i);
		if (!enviroment)
			enviroment = current;
		else
		{
			envp = enviroment;
			while (envp->next != NULL)
				envp = envp->next;
			envp->next = current;
		}
	}
	return (enviroment);
}

int	ft_envp(t_cmd *to_pars)
{
	t_cmd	*next;

	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "env") == 0)
		{
			next = to_pars->next;
			if (!next)
				return (2);
			else
				return (1);
		}
		to_pars = to_pars->next;
	}
	return (0);
}
