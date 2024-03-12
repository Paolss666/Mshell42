/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_expand_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:08:47 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:29:15 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_join_not_expand(t_expp *e)
{
	e->tmp = e->expanded_value;
	e->expanded_value = ft_strnjoin(e->expanded_value, e->value, 1);
	if (garbagge(ADD, e->expanded_value, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	garbagge(FREE, e->tmp, PARS);
	e->value++;
}

int	ft_prep_expand(t_expp *e)
{
	e->dollar = ft_strchr(e->value, '$');
	if (!e->dollar)
	{
		e->expanded_value = expand_last_dollar(e->expanded_value, e->value);
		return (1);
	}
	e->len_tot = e->dollar - e->value;
	if (e->len_tot > 0)
		e->expanded_value = cretion_sub_string(e->value,
				e->len_tot, e->expanded_value);
	return (0);
}

int	ft_join_exp_quote(t_expp *e)
{
	ft_inc_quote(*e->value, &e->q.d_q, &e->q.s_q);
	e->tmp = e->expanded_value;
	e->expanded_value = ft_strnjoin(e->expanded_value, e->value, 1);
	if (garbagge(ADD, e->expanded_value, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	garbagge(FREE, e->tmp, PARS);
	e->value++;
	return (0);
}

/*
I caratteri validi per il nome di una variabile sono lettere,
Verifica se il carattere c è valido per il nome di una variabile
Trova il prossimo dollaro
Se non ci sono più dollari, aggiungi il resto della stringa e termina
Trova la parte della stringa prima del dollaro
Controlla se il dollaro è seguito da
uno spazio o da un carattere non valido per il nome della variabile
Aggiungi il dollaro alla stringa espansa senza espanderlo
Espandi la variabile
Se la variabile non è stata trovata,
aggiungi solo il dollaro all'expanded_value
expanded_value = ft_strnjoin(expanded_value, dollar, 1); 
*/

char	*ft_expand_value(char *arg_value, int i, t_envp *environment,
			int err)
{
	t_expand		*expand;
	t_expp			e;

	e.value = arg_value;
	e.q = ini_for_quote();
	e.expanded_value = ft_strdup("");
	if (!e.expanded_value || garbagge(ADD, e.expanded_value, PARS))
		return (NULL);
	while (*e.value)
	{
		if ((*e.value == '\'' || *e.value == '"') && !ft_join_exp_quote(&e))
			continue ;
		if (e.q.s_q % 2 == 0 && *e.value == '$')
		{
			if (ft_prep_expand(&e))
				break ;
			expand = init_structure_expand(i, err, e.dollar);
			process_expand(&e.value, &e.expanded_value, expand, environment);
		}
		else
			ft_join_not_expand(&e);
	}
	return (e.expanded_value);
}
