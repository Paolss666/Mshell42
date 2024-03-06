/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:23:27 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/05 22:13:09 by npoalett         ###   ########.fr       */
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
			printf("%s", arg_cmd->cmd);
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

size_t	funny_c_echo_logic(const char *cmd, size_t idx, size_t cmd_len)
{
	while (idx < cmd_len && cmd[idx] != '\0')
	{
	    if (cmd[idx] == '-' && cmd[idx + 1] == 'n') 
		{
	        idx++; 
	        if (cmd[idx + 1] == 'n' || cmd[idx + 1] == ' ' || cmd[idx + 1] == '\0')
	            idx += 2; 
			else
	            return (idx);
	    } 
		else 
	        if (cmd[idx] != ' ' && cmd[idx] != 'n')
	            return (idx);
	    idx++;
	}
	return(0);
}

/* 	return (0); // "echo -n" non trovato, quindi non ci sono caratteri non validi
	ptr += echo_n_len; // Salta "echo" ma include il primo '-n'
	idx = ptr - cmd; // Calcola l'indice del primo carattere dopo "echo" */

size_t find_next_non_n_index(const char *cmd)
{
	const char *echo_n;
	size_t echo_n_len;
	const char *ptr;
	size_t idx;
	size_t cmd_len;
	size_t find;
	
	echo_n = "echo ";
	echo_n_len = ft_strlen(echo_n);
	ptr = ft_strstr(cmd, echo_n);
	if (ptr == NULL)
		return (0);
	ptr += echo_n_len;
	idx = ptr - cmd;
	cmd_len = ft_strlen(cmd);
	find = funny_c_echo_logic(cmd, idx, cmd_len);
	if (find)
		return (find);
	return (0);
}

char *ft_strcp_for_me(char *dest, const char *src)
{
    char *temp;
	
	temp = dest;
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
    return temp;
}

// Funzione che restituisce il token successivo non valido dopo "echo -n"
char *find_next_non_n_token(const char *cmd)
{
    long unsigned int idx;
	size_t cmd_len;
	char *result;
	
	idx = find_next_non_n_index(cmd);
    if (idx == 0)
        return (NULL);
    cmd_len = ft_strlen(cmd);
    result = malloc(cmd_len - idx + 1);
	if (!result || garbagge(ADD, result, PARS))
		return (NULL);
    if (result != NULL)
        ft_strcp_for_me(result, &cmd[idx]);
    return result;
}


int	echo_flag_funny(t_cmd *to_pars, t_cmd *arg_cmd, int error_status)
{
	char *str;
	
	str = find_next_non_n_token(to_pars->cmd);
	if(!str)
		error_status = logic_print_echo_flag(to_pars, error_status);
	else
	{
		printf("%s ", str);
		arg_cmd = to_pars->next;
		error_status = found_echo_not_flag(arg_cmd);
	}
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
		else if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo -n") == 0)
			error_status = logic_print_echo_flag(to_pars, error_status);
		else if (to_pars->cmd && ft_strncmp(to_pars->cmd, "echo -n", ft_strlen("echo -n")) == 0)
				error_status = echo_flag_funny(to_pars, arg_cmd, error_status);
		to_pars = to_pars->next;
	}
	return (error_status);
}
