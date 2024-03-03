/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_gb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:00 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/03 09:21:45 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void find_and_terminate_token(char **ptr)
{
    while (**ptr != ' ' && **ptr != '\0' && **ptr != '"' && **ptr != '\'')
        (*ptr)++;  // Continua a scorrere fino a trovare uno spazio o una virgoletta
    if (**ptr != '\0')
	{
        **ptr = '\0';  // Termina il token allo spazio o alla virgoletta
        (*ptr)++;  // Passa oltre lo spazio o la virgoletta
    }
}

int find_missing_quote(char **ptr, char quote)
{
    while (**ptr != '\0' && **ptr != quote)
        (*ptr)++;  // Continua a scorrere finché non trovi un'altra virgoletta
    if (**ptr == '\0')
        return (-1);  // Errore: mancante virgoletta di chiusura
    return (0);  // La virgoletta di chiusura è stata trovata correttamente
}


int handle_quotes(char **ptr, char quote, char *tokens[], int *i)
{
    (*ptr)++;  // Passa oltre la virgoletta
    tokens[(*i)++] = *ptr;  // Aggiunge il punto di inizio del token
    if (find_missing_quote(ptr, quote) == -1)
        return (-1);  // Errore: mancante virgoletta di chiusura
    **ptr = '\0';  // Termina il token alla virgoletta di chiusura
    (*ptr)++;  // Passa oltre la virgoletta di chiusura
    return (0);  // Operazione completata con successo
}

int split_by_quotes_and_spaces(char *str, char *tokens[])
{
    int i;
    char *ptr;

	i = 0;
	ptr = str;
    while (*ptr != '\0')
	{
        while (*ptr == ' ')
            ptr++;
        if (*ptr == '\0')
            break;
        if (*ptr == '"' || *ptr == '\'')
		{
		    if (handle_quotes(&ptr, *ptr, tokens, &i) == -1)
		        return -1;  // Errore: mancante virgoletta di chiusur
		}
		else
		{
            tokens[i++] = ptr;  // Aggiunge il punto di inizio del token
			find_and_terminate_token(&ptr);
        }
    }
    tokens[i] = NULL;  // Termina l'array con un puntatore NULL
    return (i);  // Restituisce il numero di token trovati
}
