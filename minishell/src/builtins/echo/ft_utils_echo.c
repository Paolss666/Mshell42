/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:07 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 14:17:36 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


char    *funny_commande_echo(const char *next_command)
{
    size_t  command_length;
    char    *result;

    command_length = ft_strlen(next_command);
    result = malloc(command_length + 1);
    if (garbagge(ADD, result, PARS))
        return ((garbagge(FLUSH, NULL, ALL), exit(99)), NULL);
    if (result != NULL)
    {
        ft_strcpy(result, next_command, ft_strlen(next_command));
        return (result);
    }
    return(NULL);
}

char *get_first_non_n_token(const char *cmd)
{
    const char *token;
    const char *delimiter;
    const char *next_command;
    const char *first_delimiter;
    const char *next_command_start;
    size_t		token_length;

    token = "echo -n";
    delimiter = " ";
    token_length = ft_strlen(token);
    next_command_start = ft_strstr(cmd, token) + token_length;
    if (next_command_start == NULL)
        return (NULL);
   first_delimiter = ft_strchr(next_command_start, delimiter[0]);
    if (first_delimiter == NULL)
        return (NULL);
    next_command = first_delimiter;
    while (*next_command == ' ')
        next_command++;
    if (ft_strncmp(next_command, "-n", 2) != 0)
        return (funny_commande_echo(next_command));
    return (NULL);
}

int ft_check_flag(char *flag, int i, int j) // modif gaga
{
    while (flag[i])
    {
        if (flag[i] != 'n' && flag[i] != '\0')
        {
            if (flag[i] == ' ' && flag[i + 1] 
                && flag[i + 1] == '-' && flag[i + 2])
				{
					j = i + 1;
                	return (ft_check_flag(flag, i + 2, j));
				}
			if (j == 0)
            	return (-2);
			return (j);
        }
        i++;
    }
    return (-1);
}


int    found_echo(t_cmd *to_pars) // MODIF GAGA
{
    char    *vl;
    char *tmp;
    int j;

    vl = NULL;
    tmp = ft_strdup(to_pars->cmd);
    if(!tmp || garbagge(ADD, tmp, PARS))
            (garbagge(FLUSH, NULL, ALL), exit(99));
    remove_q(tmp);
    if (ft_strcmp(tmp, "echo") == 0)
    {
        to_pars->cmd = ft_strdup("echo");
        if(!to_pars->cmd  || garbagge(ADD, to_pars->cmd , PARS))
            (garbagge(FLUSH, NULL, ALL), exit(99));
        return (garbagge(FREE, tmp, PARS), 1);
    }
    if (ft_strncmp(tmp, "echo -n", ft_strlen("echo -n")) == 0) {
        if (ft_check_flag(tmp + 6, 0, 0) == -1)
        {
            to_pars->cmd = ft_strdup("echo -n");
            if(!to_pars->cmd  || garbagge(ADD, to_pars->cmd , PARS))
                (garbagge(FLUSH, NULL, ALL), exit(99));
            return (garbagge(FREE, tmp, PARS), 2);
        }
    }
    if (ft_strncmp(tmp, "echo -", 6) == 0)
    {
        vl = ft_substr(tmp, 5, ft_strlen(tmp));
        if(!vl || garbagge(ADD, vl, PARS))
            return (-1);
        remove_q(vl);
        j = ft_check_flag(vl + 1, 0, 0);
        if (j > -1)
        {
            if (j > -1)
                printf("%s ", vl + j + 1);
            to_pars->cmd = NULL;
            to_pars->cmd = ft_strdup("echo -n");
        }
        else
        {
            printf("%s ", vl); 
        /* garbagge(FREE, to_pars->cmd, PARS); */
            to_pars->cmd = NULL;
            to_pars->cmd = ft_strdup("echo");
        }
        if(!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
            return (-1);
        return (garbagge(FREE, tmp, PARS), 1);
    garbagge(FREE, tmp, PARS);
    }
    return (0);
}

// int    found_echo(t_cmd *to_pars) // modif gaga
// {
//     char    *vl;
// 	int j;

//     vl = NULL;
//     while (to_pars != NULL)
//     {
//         if (ft_strcmp(to_pars->cmd, "echo") == 0)
//             return (printf("sono qua\n"), 1);
//         if (ft_strncmp(to_pars->cmd, "echo -n", ft_strlen("echo -n")) == 0) {
//             if (ft_check_flag(to_pars->cmd + 6, 0, 0) == -1)
//                 return (2);
//         }
//         if (ft_strncmp(to_pars->cmd, "echo -", 6) == 0)
//         {
//             vl = ft_substr(to_pars->cmd, 5, ft_strlen(to_pars->cmd));
//             if(!vl || garbagge(ADD, vl, PARS))
//                 return (-1);
//             remove_q(vl);
// 			printf("vl %s\n", vl);
// 			j = ft_check_flag(vl + 1, 0, 0);
// 			if (j > -1)
// 			{
// 				if (j > -1)
// 					printf("%s ", vl + j + 1);
// 				to_pars->cmd = NULL;
//             	to_pars->cmd = ft_strdup("echo -n");
// 			}
// 			else
// 			{
//             	printf("%s ", vl); 
//             	to_pars->cmd = NULL;
//             	to_pars->cmd = ft_strdup("echo");
// 			}
//             if(!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
//                 return (-1);
//             return (1);
//         }
//         to_pars = to_pars->next;
//     }
//     return (0);
// }

// int	found_echo(t_cmd *to_pars)
// {
// 	char	*vl;

// 	vl = NULL;
// 	while (to_pars != NULL)
// 	{
// 		if (ft_strcmp(to_pars->cmd, "echo") == 0)
// 			return (1);
// 		if (ft_strncmp(to_pars->cmd, "echo -n", ft_strlen("echo -n")) == 0)
// 			return (2);
// 		if (ft_strncmp(to_pars->cmd, "echo -", 6) == 0)
// 		{
// 			vl = ft_substr(to_pars->cmd, 4, ft_strlen(to_pars->cmd));
// 			if(!vl || garbagge(ADD, vl, PARS))
// 				return (-1);
// 			remove_q(vl);
// 			printf("%s", vl); 
// 			/* garbagge(FREE, to_pars->cmd, PARS); */
// 			to_pars->cmd = NULL;
// 			to_pars->cmd = ft_strdup("echo");
// 			if(!to_pars->cmd || garbagge(ADD, to_pars->cmd, PARS))
// 				return (-1);
// 			return (1);
// 		}
// 		to_pars = to_pars->next;
// 	}
// 	return (0);
// }

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

