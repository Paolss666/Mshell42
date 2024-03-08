/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_gb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:47:00 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/08 15:03:39 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Continua a scorrere fino a trovare uno spazio o una virgoletta
// Termina il token allo spazio o alla virgoletta
// Passa oltre lo spazio o la virgoletta

void find_and_terminate_token(char **ptr)
{
    while (**ptr != ' ' && **ptr != '\0' && **ptr != '"' && **ptr != '\'')
        (*ptr)++;
    if (**ptr != '\0')
	{
        **ptr = '\0';
        (*ptr)++;
    }
}

// Continua a scorrere finché non trovi un'altra virgoletta
// Errore: mancante virgoletta di chiusura
// La virgoletta di chiusura è stata trovata
// Errore: mancante virgoletta di chiusura

int find_missing_quote(char **ptr, char quote)
{
    while (**ptr != '\0' && **ptr != quote)
        (*ptr)++;
    if (**ptr == '\0')
        return (-1);
    return (0);  
}


int handle_quotes(char **ptr, char quote, char *tokens[], int *i)
{
    if(*ptr && tokens[(*i)])
    {
        (*ptr)++;  // Passa oltre la virgoletta
        tokens[(*i)++] = *ptr;  // Aggiunge il punto di inizio del token
        if (find_missing_quote(ptr, quote) == -1)
            return (-1);  // Errore: mancante virgoletta di chiusura
    }
    **ptr = '\0';  // Termina il token alla virgoletta di chiusura
    if(*ptr)
        (*ptr)++;  // Passa oltre la virgoletta di chiusura
    return (0);  // Operazione completata con successo
}

int handle_quotes_with(char **ptr, char quote, char *tokens[], int *i)
{
   /*  (*ptr)++;   */// Passa oltre la virgoletta
    printf("tokens[*i] = %s\n", tokens[*i]);
    tokens[(*i)++] = *ptr;  // Aggiunge il punto di inizio del token
    printf("tokens[*i] = %s\n", tokens[*i]);
    if (find_missing_quote(ptr, quote) == -1)
        return (-1);  // Errore: mancante virgoletta di chiusura
    **ptr = '\0';  // Termina il token alla virgoletta di chiusura
    (*ptr)++;  // Passa oltre la virgoletta di chiusura
    return (0);  // Operazione completata con successo
}

int split_by_quotes_and_spaces(char *str, char *tokens[], int flag)
{
    int i;
    char *ptr;

	i = 0;
	ptr = str;
    print_string_array(tokens);
    printf("\n\nSPLIT str _%s_\n", str);
    while (*ptr != '\0')
	{
        printf("DEBUT BOUCLE token[%d] %s *ptr=|%c|\n", i,  tokens[i], *ptr);
        while (*ptr == ' ')
            ptr++;
        if (*ptr == '\0')
            break;
        if (*ptr == '"' || *ptr == '\'')
		{
            printf("IF QUOTE *ptr=|%c|\n", *ptr);
            if (flag)
            {
                if (handle_quotes_with(&ptr, *ptr, tokens, &i) == - 1)
                    return(-1);
            }
            else
            {
                printf("ELSE DEBUT i %d, *ptr |%c|\n", i, *ptr);
                if (handle_quotes(&ptr, *ptr, tokens, &i) == -1)
		            return (-1);  // Errore: mancante virgoletta di chiusur
                printf("ELSE DEBUT  i %d, *ptr |%c|\n", i, *ptr);
            }
		}
		else
		{
            printf("tokens[i] = %s\n", tokens[i]);
            tokens[i++] = ptr;  // Aggiunge il punto di inizio del token
            printf("tokens[i] = %s\n", tokens[i]);
			find_and_terminate_token(&ptr);
            printf("FIN ELSE token[%d] %s\n", i - 1,  tokens[i - 1]);
        }
    }
    print_string_array(tokens);
    // tokens[i] = NULL;  // Termina l'array con un puntatore NULL
    return (i);  // Restituisce il numero di token trovati
}
