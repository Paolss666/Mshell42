/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:37 by npaolett          #+#    #+#             */
/*   Updated: 2024/02/28 14:26:02 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE ECHO  */

extern int	g_signal_received;



// modif mais ne marche pas strcmp pas bonne etc etc
char	*find_variable_value(char *var_name, t_envp *enviroment, int e_st)
{
	char	*found_egual;
	char	*value;

	value = NULL;
	if (!var_name)
		return (NULL);
	if (!ft_strcmp(var_name, "?"))
		return (logic_f_dollar_int(var_name, e_st));
	while (enviroment != NULL)
	{
		if (ft_strcmp(enviroment->name, var_name) == 0)
		{
			found_egual = ft_strchr(enviroment->path, '=');
			value = ft_strdup(found_egual + 1);
			if (!value || garbagge(ADD, value, ENV))
				return (ft_putstr_fd("Fail malloc strdup\n", 2), NULL);
			return (value);
		}
		else
			enviroment = enviroment->next;
	}
	return (NULL);
}

char	*found_chr_forjoin(t_cmd *to_pars)
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
}

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

char	*before_dollar(char *s)
{
	size_t	i;
	char	*before;

	i = 0;
	before = NULL;
	if (!s)
		return (NULL);
	while (s[i] != '$' && s[i])
		i++;
	before = ft_substr(s, 0, i);
	if (!before || garbagge(ADD, before, PARS))
		return (NULL);
	return (before);
}

char	*before_dollar_alone(char *s)
{
	size_t	i;
	char	*before;

	i = 1;
	before = NULL;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '$')
		i++;
	before = ft_substr(s, 0, i);
	if (!before || garbagge(ADD, before, PARS))
		return (NULL);
	return (before);
}

char	*if_before(char *before, char *var_value)
{
	if ((before && var_value))
	{
		var_value = ft_strjoin(before, var_value);
		if (!var_value || garbagge(ADD, var_value, PARS))
			return (NULL);
		garbagge(FREE, before, PARS);
		before = NULL;
		return (var_value);
	}
	else
		return (before);
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



char	*ft_strnjoin(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	char	*result;
	size_t	j;

	len_s1 = 0;
	len_s2 = 0;
	result = NULL;
	while (s1[len_s1])
		len_s1++;
	while (s2[len_s2] && len_s2 < n)
		len_s2++;
	result = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	i = len_s1;
	j = 0;
	while (s2[j] && j < n)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
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

char	*cretion_sub_string(char *value, int len_tot, char *expanded_value)
{
	char	*sub_s;

	sub_s = ft_substr(value, 0, len_tot);
	if (!sub_s || garbagge(ADD, sub_s, PARS))
		return (garbagge(FLUSH, NULL, ALL), NULL);
	expanded_value = ft_strjoin(expanded_value, sub_s);
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	return (expanded_value);
}

char	*expnad_join_dollar(char *expanded_value, char *dollar)
{
	expanded_value = ft_strnjoin(expanded_value, dollar, 1);
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	return (expanded_value);
}

char	*expand_last_dollar(char *expanded_value, char *value)
{
	expanded_value = ft_strjoin(expanded_value, value);
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	return (expanded_value);
}

char	*expanded_var_value(char *var_value, char *expanded_value)
{
	if (var_value)
	{
		expanded_value = ft_strjoin(expanded_value, var_value);
		if (!expanded_value || garbagge(ADD, expanded_value, PARS))
			return (garbagge(FLUSH, NULL, ALL), exit(1), NULL);
	}
	return (expanded_value);
}

void	process_expand(char **value, char **expanded_value, t_expand *expand,
		t_envp *environment)
{
	char	*var_name;
	char	*var_value;

	if (expand->dollar[1] == ' ' || !is_valid_variable_char(expand->dollar[1]))
	{
		*expanded_value = expnad_join_dollar(*expanded_value, expand->dollar);
		*value = expand->dollar + 1;
	}
	else
	{
		var_name = creation_var_name(1, expand->i, expand->dollar);
		var_value = find_variable_value(var_name, environment,
				expand->err);
		if (var_value)
			*expanded_value = expanded_var_value(var_value, *expanded_value);
		*value = expand->dollar + ft_strlen(var_name) + 1;
	}
}

t_expand	*init_structure_expand(int i, int err, char *dollar)
{
	t_expand	*expand;

	expand = (t_expand *)malloc(sizeof(t_expand));
	if (!expand || garbagge(ADD, expand, PARS))
		return (NULL);
	expand->dollar = ft_strdup(dollar);
	if (!expand->dollar || garbagge(ADD, expand->dollar, PARS))
		return (garbagge(FREE, expand, PARS), NULL);
	expand->i = i;
	expand->err = err;
	return (expand);
}

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
			printf("%s ", arg_cmd->cmd);
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
		if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo -n") == 0)
			error_status = logic_print_echo_flag(to_pars, error_status);
		to_pars = to_pars->next;
	}
	return (error_status);
}
