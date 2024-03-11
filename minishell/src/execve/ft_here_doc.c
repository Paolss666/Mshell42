/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:14:19 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 14:21:05 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

extern int	g_signal_received;

char	*expand_dollar_here_doc(int fd, char *line, t_envp *environment)
{
	char	*no_dollar;

	no_dollar = line;
	while (environment && line && line[0] == '$'
		&& valid_variable_char(line[1]))
	{
		if (line[0] == '$')
		{
			no_dollar = ft_strtrim(line, "$");
			if (!no_dollar || garbagge(ADD, no_dollar, PARS))
				return (NULL);
		}
		if (ft_strcmp(no_dollar, environment->name) == 0)
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			line = ft_strdup(environment->value);
			if (!line || garbagge(ADD, line, PARS))
				return (garbagge(FREE, no_dollar, PARS), NULL);
		}
		environment = environment->next;
	}
	return (line);
}

int	hdoc_signint(int fd)
{
	if (open("/dev/stdout", O_RDONLY) == -1)
		return (close(fd), perror("open :"), 0);
	return (close(fd), 1);
}

void	found_cntr_c(int fd, t_file *file, char *line)
{
	hdoc_signint(fd);
	unlink(file->nome_file);
	free(line);
	set_signal_action(1);
}

int	read_here_doc(int fd, t_file *file, t_envp *enviroment)
{
	char	*line;

	while (1)
	{
		set_signal_action(2);
		line = readline(">");
		if (g_signal_received == 60)
			return (found_cntr_c(fd, file, line), 1);
		if (!line)
			break ;
		line = ft_strdup(expand_dollar_here_doc(fd, line, enviroment));
		if (!line || garbagge(ADD, line, ENV))
			break ;
		remove_q(file->nome_file);
		if (ft_strcmp(line, file->nome_file) == 0)
			break ;
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			exit(EXIT_FAILURE);
		add_history(line);
	}
	if (!line)
	{
		garbagge(FREE, NULL, ENV);
		g_signal_received = 127;
	}
	return (close(fd), set_signal_action(1), 0);
}


int	create_here_doc_file(char *here_doc)
{
	int	fd;

	fd = open(here_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error creating here_doc file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}



int	ft_found_here_doc(t_file *new_node, char *here_doc, int fd_here_doc_input,
		int fd_here_doc_output, t_envp *enviroment)
{
	new_node->here_doc = ft_strdup(here_doc);
	if (!new_node->here_doc || garbagge(ADD, new_node->here_doc, EX))
		return (2);
	fd_here_doc_input = create_here_doc_file(new_node->here_doc);
	fd_here_doc_output = dup(fd_here_doc_input);
	if (fd_here_doc_output == -1)
		perror("fd_here_doc_output");
	new_node->here_doc_fd = fd_here_doc_output;
	if (read_here_doc(fd_here_doc_input, new_node, enviroment))
	{
		close(fd_here_doc_input);
		close(fd_here_doc_output);
		return (1);
	}
	close(fd_here_doc_input);
	close(fd_here_doc_output);
	return (0);
}