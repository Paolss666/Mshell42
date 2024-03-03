/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:27:26 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/03 13:51:56 by npoalett         ###   ########.fr       */
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

char	*found_shlvl_init(char *env)
{
	int	n;
	char *value;

	value = NULL;
	n = 0;
	if(!env)
		return (NULL);
	if((ft_strncmp(env, "SHLVL=", 6) == 0))
	{
		value  = ft_strchr(env, '=') + 1;
		n = ft_atoi(value) + 1;
		value  = ft_itoa(n);
		if(!value || garbagge(ADD, value, ENV))
			return (NULL);
		env = ft_strjoin("SHLVL=", value);
		if (!env || garbagge(ADD, env, ENV))
			return(garbagge(FLUSH, NULL, ALL), exit(124), NULL);
		return(env);
	}
	return(NULL);
}


t_envp	*create_enviroment(char **env, int i)
{
	int		len;
	t_envp *current;
	char	*shlvl;

	len = 0;
	current = (t_envp *)malloc(sizeof(t_envp));
	if (!current || garbagge(ADD, current, ENV))
		return (perror("FAIL malloc t_envp"), NULL);
	shlvl = found_shlvl_init(env[i]);
	if(shlvl)
		env[i] = shlvl;
	current->path = env[i];
	current->value = ft_strdup(ft_strchr(current->path, '=') + 1);
	if (!current->value || garbagge(ADD, current->value, ENV))
		return (garbagge(FREE, current->path, ENV), NULL);
	len = ft_strlen(current->path) - ft_strlen(current->value);
	current->name = ft_substr(current->path, 0, len - 1);
	if (!current->name || garbagge(ADD, current->name, ENV))
		return (garbagge(FREE, current->path, ENV),garbagge(FREE, current->value, ENV), NULL);
	current->next = NULL;
	return (current);
}



t_envp	*found_and_add_env(char **env, t_envp *enviroment)
{
	t_envp	*current;
	t_envp	*envp;
	int		i;

	i = -1;
	current = NULL;
	if (!env)
	{
		enviroment = create_enviroment(NULL, 0);
		return (enviroment);
	}
	while (env[++i])
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

int ft_envp(t_cmd *to_pars)
{
    t_cmd *next;

    while (to_pars != NULL)
    {
        if (ft_strcmp(to_pars->cmd, "env") == 0)
        {
            next = to_pars->next;
            if (!next)
                return 2;
            else
                return 1;
        }
        to_pars = to_pars->next;
    }
    return 0;
}

void	print_list_envp(t_envp *head)
{
	t_envp	*current;

	if (!head)
	{
		current = (t_envp *)malloc(sizeof(t_envp));
		if (!current || garbagge(ADD, current, ENV))
			return ((void)0);
		current->name = NULL;
		current->path = NULL;
		current->value = NULL;
		head = current;
		return ((void)0);
	}
	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->path);
		current = current->next;
	}
}
