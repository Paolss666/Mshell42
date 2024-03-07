/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:02:33 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/06 17:39:12 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_is_all_space(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 999;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			flag = 0;
		i++;
	}
	return (flag);
}

int	ft_error_line_saver(char *str)
{
	char	*error_message;

	error_message = "bash syntax error near unexpected token '&&'";
	if (ft_error_blank(str) == 999)
		return (999);
	if (ft_error_pipe(str))
		return (2);
	if (ft_error_shift_operator(str))
		return (2);
	if (ft_error_directoryx(str))
		return (126);
	if (ft_error_operand(str, error_message))
		return (2);
	if (ft_error_parenthesis(str))
		return (2);
	if (ft_error_semicol(str))
		return (2);
	if (ft_error_bracket(str))
		return (2);
	return (0);
}

int	is_error(char *str)
{
	int	error;

	if (!str)
		return (999);
	if (str && str[0] && ft_strlen(str) == 1)
	{
		error = ft_error_case_1(str[0]);
		if (error)
			return (error);
	}
	if (ft_is_all_space(str))
		return (999);
	ft_handle_quote(str);
	error = ft_error_line_saver(str);
	if (error)
		return (error);
	return (0);
}

int	check_forbiden_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = '\v';
	if (!str)
		return (1);
	c = check_forb_logic(i, c, str);
	if (c == '\'')
		return (printf("bash: syntax error near unexpected token '''\n"), 1);
	if (c == '"')
		return (printf("bash: syntax error near unexpected token '\"'\n"), 2);
	return (0);
}

int	error_manager(char *str)
{
	int		error;

	if (!str)
		return (0);
	error = check_forbiden_quote(str);
	if (error)
		return (error);
	error = is_error(str);
	if (error)
		return (error);
	return (0);
}
