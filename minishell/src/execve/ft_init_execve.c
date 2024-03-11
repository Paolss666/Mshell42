/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:43:18 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 14:13:38 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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


void	add_node_logic(t_file **file_list, t_file *temp, t_file *new_node)
{
	if (*file_list == NULL)
		*file_list = new_node;
	else
	{
		temp = *file_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_file	*init_new_node_redir(t_file *new_node, t_cmd *to_pars)
{
	new_node = (t_file *)malloc(sizeof(t_file));
	if (!new_node || garbagge(ADD, new_node, EX))
		return (perror("Fail malloc for file node"), NULL);
	new_node->redir = ft_strdup(to_pars->cmd);
	if (!new_node->redir || garbagge(ADD, new_node->redir, EX))
		return (garbagge(FREE, new_node, EX), NULL);
	new_node->nome_file = ft_strdup(to_pars->next->cmd);
	if (!new_node->nome_file || garbagge(ADD, new_node->nome_file, EX))
		return (garbagge(FREE, new_node->redir, EX), garbagge(FREE, new_node,
				EX), NULL);
	new_node->next = NULL;
	return (new_node);
}

int	add_file_node(t_file **fileList, t_cmd *to_pars, char *here_doc,
		t_envp *enviroment)
{
	t_file	*new_node;
	t_file	*temp;
	int		fd_here_doc_input;
	int		fd_here_doc_output;

	temp = NULL;
	new_node = NULL;
	fd_here_doc_output = 0;
	fd_here_doc_input = 0;
	if (!new_node)
		new_node = init_new_node_redir(new_node, to_pars);
	if (here_doc)
	{
		if (ft_found_here_doc(new_node, here_doc, fd_here_doc_input,
				fd_here_doc_output, enviroment) == 1)
			return (1);
	}
	else
	{
		here_doc = NULL;
		new_node->here_doc_fd = 0;
	}
	if (fileList)
		add_node_logic(fileList, temp, new_node);
	return (0);
}

char	**export_list_to_exp_env(t_exp *enviroment)
{
	char	**new_enviroment;
	int		i;

	i = 0;
	new_enviroment = (char **)malloc(sizeof(char *) * len_liste_exp(enviroment)
			+ 1);
	if (!new_enviroment || garbagge(ADD, new_enviroment, ENV))
		return (NULL);
	if (!enviroment || len_liste_exp(enviroment) <= 0)
		return (NULL);
	while (enviroment)
	{
		new_enviroment[i] = ft_strdup(enviroment->path);
		if (!new_enviroment[i] || garbagge(ADD, new_enviroment[i], ENV))
			return (ft_free_tab_garbage(new_enviroment), NULL);
		enviroment = enviroment->next;
		i++;
	}
	new_enviroment[i] = NULL;
	return (new_enviroment);
}




void initialize_file_descriptors(t_execve *pipe)
{
    int i;

	i = 0;
	pipe->get_g_path = NULL;
	pipe->good_cmd = NULL;
	pipe->for_h = 0;
    while (i < pipe->n_pipe)
	{
        pipe->tmp_fd[i][0] = 0;
        pipe->tmp_fd[i][1] = 0;
        i++;
    }
    pipe->fd[0] = 0;
    pipe->fd[1] = 1;
}

int	found_redir(t_cmd *to_pars, t_envp *enviroment, t_file **file_list)
{
	int	sign;

	sign = 0;
	if (ft_strcmp(to_pars->cmd, "<") == 0 && to_pars->next)
		add_file_node(file_list, to_pars, NULL, enviroment);
	else if (ft_strcmp(to_pars->cmd, ">") == 0 && to_pars->next)
		add_file_node(file_list, to_pars, NULL, enviroment);
	else if (ft_strcmp(to_pars->cmd, ">>") == 0 && to_pars->next)
		add_file_node(file_list, to_pars, NULL, enviroment);
	else if (ft_strcmp(to_pars->cmd, "<<") == 0 && to_pars->next)
		sign = add_file_node(file_list, to_pars, to_pars->next->cmd,
				enviroment);
	return (sign);
}

int	ft_cpy_list_redirection(int i, t_cmd *to_pars, t_envp *enviroment,
		t_file ***list_array)
{
	t_file	**file_list;
	int		sign;

	sign = 0;
	while (to_pars && list_array[i])
	{
		file_list = (t_file **)malloc(sizeof(t_file *));
		if (!file_list || garbagge(ADD, file_list, EX))
			return (1);
		*file_list = NULL;
		while (to_pars && ft_strcmp(to_pars->cmd, "|") != 0)
		{
			sign = found_redir(to_pars, enviroment, file_list);
			if (sign)
				return (1);
			to_pars = to_pars->next;
		}
		list_array[i] = file_list;
		i++;
		if (to_pars)
			to_pars = to_pars->next;
	}
	return (0);
}

t_file	***ft_cpy_list_redir2(int i, t_execve *pipe, t_file ***list_array)
{
	while (i < pipe->n_pipe)
	{
		list_array[i] = (t_file **)malloc(sizeof(t_file *));
		if (!list_array[i] || garbagge(ADD, list_array[i], EX))
			return (garbagge(FLUSH, NULL, EX), NULL);
		*(list_array[i]) = NULL;
		i++;
	}
	return (list_array);
}


t_execve	*init_structure(t_envp *enviroment, t_cmd *to_pars, t_exp *export, int	error_status)
{
	t_execve	*pipe;
	int			i;
	t_file		***list_array;

	pipe = (t_execve *)malloc(sizeof(t_execve));
	if (!pipe || garbagge(ADD, pipe, EX))
		return (NULL);
	pipe->n_pipe = 1 + found_count_pipe(to_pars);
	pipe->new_enviroment = envp_list_to_new_env(enviroment);
	pipe->exp = export_list_to_exp_env(export);
	pipe->token = found_infile_or_endfile(to_pars);
	list_array = (t_file ***)malloc(pipe->n_pipe * sizeof(t_file **));
	if (!list_array || garbagge(ADD, list_array, EX))
		return (garbagge(FLUSH, NULL, EX), NULL);
	i = 0;
	list_array = ft_cpy_list_redir2(i, pipe, list_array);
	i = 0;
	if (ft_cpy_list_redirection(i, to_pars, enviroment, list_array) == 1)
		return (NULL);
	pipe->current_pipe = 0;
	pipe->error = error_status;
	pipe->pid[pipe->current_pipe] = 0;
	pipe->pipe_redirections = list_array;
	initialize_file_descriptors(pipe);
	return (pipe);
}