/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:37 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:44:50 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal_received;


/* char	*found_chr_forjoin(t_cmd *to_pars)
{
	char	*value;
	char	*current;
	int		i;

	i = 0;
	current = to_pars->cmd;
	while (current[i] && is_special_char(current[i]))
		i++;
	while ((current[i] && !is_special_char(current[i])))
		i++;
	if (current[i] && current[i + 1])
	{
		while (current[i] && is_special_char(current[i]))
			i++;
		i--;
	}
	value = ft_substr(current, i, ft_strlen(current) - i);
	if (!value || garbagge(ADD, value, PARS))
		return (NULL);
	garbagge(FREE, current, PARS);
	return (value);
} */

int	print_not_found(int print_argument, t_cmd *arg_cmd)
{
	char	*trim;

	trim = NULL;
	if (print_argument && arg_cmd->cmd != NULL && arg_cmd->cmd[0] != '\0')
	{
		if (ft_strchr(arg_cmd->cmd, '\''))
		{
			trim = ft_strtrim(arg_cmd->cmd, "\'");
			if (!trim || garbagge(ADD, trim, PARS))
				return (0);
			printf("%s ", trim);
		}
		else
			printf("%s ", arg_cmd->cmd);
		return (print_argument);
	}
	else
		print_argument = 1;
	return (print_argument);
}

int	ft_condition_printf(int print_argument, t_cmd *arg_cmd,
		char *expanded_value)
{
	if ((arg_cmd))
	{
		if (expanded_value)
		{
			arg_cmd->cmd = expanded_value;
			print_argument = 0;
		}
	}
	else
	{
		if (expanded_value)
			printf("%s ", expanded_value);
		else
			return (20);
	}
	return (print_argument);
}

int	logic_display_error(t_cmd *arg_cmd)
{
	char	*trim;

	trim = NULL;
	if (ft_strcmp(arg_cmd->cmd, "|") == 0 || ft_strcmp(arg_cmd->cmd, "<") == 0
		|| ft_strcmp(arg_cmd->cmd, ">>") == 0 || ft_strcmp(arg_cmd->cmd,
			">") == 0 || ft_strcmp(arg_cmd->cmd, "<<") == 0)
		return (1);
	if (ft_strcmp(arg_cmd->cmd, "$") == 0 && !arg_cmd->next)
	{
		printf("%s ", arg_cmd->cmd);
		return (1);
	}
	if (arg_cmd->cmd && arg_cmd->cmd[0] && check_if_only_space(arg_cmd->cmd)
		&& !arg_cmd->next)
	{
		trim = ft_strtrim(arg_cmd->cmd, "\"");
		if (!trim || garbagge(ADD, trim, PARS))
			return (0);
		printf("%s ", trim);
		garbagge(FREE, trim, PARS);
		trim = NULL;
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
			printf("%s ", arg_cmd->cmd);
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
		return (ft_putstr_fd("FAIL MALLOC\n", 2), NULL);
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

// I caratteri validi per il nome di una variabile sono lettere,
// Verifica se il carattere c è valido per il nome di una variabile
// Trova il prossimo dollaro
// Se non ci sono più dollari, aggiungi il resto della stringa e termina
// Trova la parte della stringa prima del dollaro
// Controlla se il dollaro è seguito da
//uno spazio o da un carattere non valido per il nome della variabile
// Aggiungi il dollaro alla stringa espansa senza espanderlo
// Espandi la variabile
// Se la variabile non è stata trovata,
//aggiungi solo il dollaro all'expanded_value
/* expanded_value = ft_strnjoin(expanded_value, dollar, 1); */


char	*ft_expand_value(char *arg_value, int i, t_envp *environment,
		int err)
{
	char		*value;
	char		*expanded_value;
	char		*dollar;
	int			len_tot;
	t_expand	*expand;

	value = arg_value;
	expanded_value = ft_strdup("");
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (NULL);
	while (*value)
	{
		dollar = ft_strchr(value, '$');
		if (!dollar)
		{
			expanded_value = expand_last_dollar(expanded_value, value);
			break ;
		}
		len_tot = dollar - value;
		if (len_tot > 0)
			expanded_value = cretion_sub_string(value, len_tot, expanded_value);
		expand = init_structure_expand(i, err, dollar);
		process_expand(&value, &expanded_value, expand, environment);
	}
	remove_q(expanded_value);
	return (expanded_value);
}

