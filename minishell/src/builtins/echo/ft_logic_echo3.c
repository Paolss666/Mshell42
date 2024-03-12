/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_echo3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:41:25 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 00:29:04 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

void	remove_quote(char *s)
{
	char	*p;
	char	*q;
	t_quote	quote;

	p = s;
	q = s;
	quote.d_q = 0;
	quote.s_q = 0;
	while (*p != '\0')
	{
		ft_inc_quote(*p, &quote.d_q, &quote.s_q);
		if ((*p != '"' && *p != '\'')
			|| ((quote.d_q % 2 == 1 && quote.s_q % 2 == 0 && *p == '\'')
				|| (quote.s_q % 2 == 1 && quote.d_q % 2 == 0 && *p == '"')))
		{
			*q = *p;
			q++;
		}
		p++;
	}
	*q = '\0';
}

size_t	find_next_non_n_index(const char *cmd)
{
	const char	*echo_n;
	size_t		echo_n_len;
	const char	*ptr;
	size_t		idx;
	size_t		find;

	echo_n = "echo ";
	echo_n_len = ft_strlen(echo_n);
	ptr = ft_strstr(cmd, echo_n);
	if (ptr == NULL)
		return (0);
	ptr += echo_n_len;
	idx = ptr - cmd;
	find = funny_c_echo_logic(cmd, idx, ft_strlen(cmd));
	if (find)
		return (find);
	return (0);
}

char	*ft_strcp_for_me(char *dest, const char *src)
{
	char	*temp;

	temp = dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (temp);
}
