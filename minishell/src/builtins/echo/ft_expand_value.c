/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:30:37 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 17:25:29 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


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

void	join_not_expand(char **value, char **expanded_value)
{
	char	*tmp;

	tmp = *expanded_value;
	*expanded_value = ft_strnjoin(*expanded_value, *value, 1);
	if (garbagge(ADD, *expanded_value, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	garbagge(FREE, tmp, PARS);
	(*value)++;
	while (**value && **value != '\'')
	{
		tmp = *expanded_value;
		*expanded_value = ft_strnjoin(*expanded_value, *value, 1);
		if (garbagge(ADD, *expanded_value, PARS))
			garbagge(FLUSH, NULL, ALL);
		garbagge(FREE, tmp, PARS);
		(*value)++;
	}
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

char    *ft_expand_value(char *arg_value, int i, t_envp *environment,
        int err)
{
	char			*value;
	char			*expanded_value;
	char			*dollar;
	int				len_tot;
	t_expand		*expand;
	char			*tmp;
	t_quote			q;

	value = arg_value;
	q = ini_for_quote();
	expanded_value = ft_strdup("");
	if (!expanded_value || garbagge(ADD, expanded_value, PARS))
		return (NULL);
	while (*value)
	{
		if (*value == '\'' || *value == '"')
		{
			ft_inc_quote(*value, &q.d_q, &q.s_q);
            tmp = expanded_value;
            expanded_value = ft_strnjoin(expanded_value, value, 1);
			if (garbagge(ADD, expanded_value, PARS))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			garbagge(FREE, tmp, PARS);
            value++;
			continue;
		}
		if (q.s_q % 2 == 0 && *value == '$')
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
		else
		{
				tmp = expanded_value;
				expanded_value = ft_strnjoin(expanded_value, value, 1);
				if (garbagge(ADD, expanded_value, PARS))
					(garbagge(FLUSH, NULL, ALL), exit(99));
				garbagge(FREE, tmp, PARS);
                value++;
		}
	}
	return (expanded_value);
}
