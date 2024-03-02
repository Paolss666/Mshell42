/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:07 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/02 10:21:26 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* void addNodeAfterDoubleDash(struct Node** head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return;

    struct Node* current = *head_ref;
    while (current != NULL) {
        char* double_dash_pos = strstr(current->data, "--");
        if (double_dash_pos != NULL && double_dash_pos == current->data) {
            // Trovato "--" come parte del valore di questo nodo
            struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
            strcpy(new_node->data, double_dash_pos + 2); // Copia il resto della stringa dopo "--"
            new_node->next = current->next; // Collega il nuovo nodo al nodo successivo del nodo corrente
            current->next = new_node; // Collega il nodo corrente al nuovo nodo
            return;
        }
        current = current->next;
    }
} */


char *get_first_non_n_token(const char *cmd) {
    const char *token = "echo -n";
    const char *delimiter = " ";
    
    // Trova la lunghezza del token "echo -n"
    size_t token_length = strlen(token);
    // Trova il punto in cui inizia il comando successivo al token "echo -n"
    const char *next_command_start = strstr(cmd, token) + token_length;
    // Trova il primo delimitatore dopo il token "echo -n"
    const char *first_delimiter = strchr(next_command_start, delimiter[0]);
    // Se non ci sono delimitatori, restituisci NULL
    if (first_delimiter == NULL)
        return NULL;
    // Trova il primo carattere del comando successivo al token "echo -n"
    const char *next_command = first_delimiter;
    while (*next_command == ' ')
        next_command++;
    // Controlla se il comando successivo è diverso da "-n"
    if (strncmp(next_command, "-n", 2) != 0) {
        // Trova la lunghezza del comando successivo
        size_t command_length = strcspn(next_command, delimiter);
        // Alloca memoria per il comando successivo
        char *result = malloc(command_length + 1);
        if (result != NULL) {
            // Copia il comando successivo nella memoria allocata
            strncpy(result, next_command, command_length);
            result[command_length] = '\0'; // Aggiunge il terminatore di stringa
            return result;
        }
    }
    return NULL; // Non trovato alcun comando diverso da "-n"
}

/* int		check_flag_quotes(t_cmd *to_pars)
{
	if (ft_strcmp(to_pars->cmd, "echo") == 0)
		if (to_pars->next != NULL && strcmp(to_pars->next->cmd, "\"-n\"") == 0)
			return(-1);
		return (2);
	return (0);
} */

int	found_echo(t_cmd *to_pars)
{
	char	*vl;

	vl = NULL;
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "echo") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "echo -n") == 0)
			return (2);
		if (ft_strncmp(to_pars->cmd, "echo -n", 7) == 0)
		{
			if (!get_first_non_n_token(to_pars->cmd))
			{ 
				garbagge(FREE, to_pars->cmd, PARS);
				to_pars->cmd = NULL;
				to_pars->cmd = ft_strdup("echo -n");
				if(!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
					return (-1);
				return (1);
			}

		}
		if (ft_strncmp(to_pars->cmd, "echo -", 6) == 0)
		{
			if (get_first_non_n_token(to_pars->cmd))
			{
				vl = get_first_non_n_token(to_pars->cmd);
				remove_q(vl);
				printf("%s ", vl); 
				garbagge(FREE, to_pars->cmd, PARS);
				to_pars->cmd = NULL;
				to_pars->cmd = ft_strdup("echo -n");
				if(!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
					return (-1);
				return (1);
			}
			else
			{
				vl = ft_substr(to_pars->cmd, 5, ft_strlen(to_pars->cmd));
				if(!vl || garbagge(ADD, vl, PARS))
					return (-1);
			}
			remove_q(vl);
			printf("%s ", vl); 
			garbagge(FREE, to_pars->cmd, PARS);
			to_pars->cmd = NULL;
			to_pars->cmd = ft_strdup("echo");
			if(!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
				return (-1);
			return (1);
		}
		to_pars = to_pars->next;
	}
	return (0);
}

int	valid_variable_char(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

char	*logic_f_dollar_int(char *current, int error_status)
{
	if (ft_strcmp(current, "?") == 0)
	{
		current = ft_itoa(error_status);
		if (!current || garbagge(ADD, current, PARS))
			return (NULL);
		return (current);
	}
	return (NULL);
}

int	is_special_char(char c)
{
	char	*special_chars;
	int		i;

	special_chars = "-[]=}{:/.+@#!?~^'\" ";
	i = 0;
	while (special_chars[i])
	{
		if (c == special_chars[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_dollar(char *string)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (string[++i])
		if (string[i] == '$')
			c++;
	return (c);
}

