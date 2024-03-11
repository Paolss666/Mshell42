/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:33:51 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 14:19:58 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void printTripleStringArray(char ***array);

extern int	g_signal_received;

int found_count_pipe(t_cmd *cmd)
{
    int pipe_count = 0;
	char *str;
    int flag = 0; // Inizializziamo il flag a 0 per indicare che non siamo all'interno di singoli o doppi apici

	while (cmd != NULL)
    {
        str = cmd->cmd;
        while (*str != '\0')
        {
            if (*str == '\'' || *str == '\"')
                flag = !flag; // Cambiamo lo stato del flag quando troviamo apici singoli o doppi
            if (*str == '|' && flag == 0)
                pipe_count++; // Contiamo solo se non siamo all'interno di apici singoli o doppi
            str++;
        }
        cmd = cmd->next;
    }
    // printf("count pipe => %d\n", pipe_count);
    return pipe_count;
}


char	*create_temp_buffer(const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*temp;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	total_len = len1 + len2 + 2;
	temp = (char *)malloc(total_len * sizeof(char));
	if (!temp || garbagge(ADD, temp, PARS))
		return (NULL);
	ft_strlcpy(temp, str1, total_len);
	ft_strlcat(temp, " ", total_len);
	ft_strlcat(temp, str2, total_len);
	return (temp);
}

void	creation_cmd(t_cmd **current_commande, const char *new_cmd)
{
	t_cmd	*new_node;
	char	*temp;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node || garbagge(ADD, new_node, PARS))
		return (perror("Memory allocation error"), exit(EXIT_FAILURE), (void)0);
	new_node->cmd = ft_strdup(new_cmd);
	if (!new_node->cmd || garbagge(ADD, new_node->cmd, PARS))
		return (garbagge(FREE, new_node, PARS), (void)0);
	new_node->next = NULL;
	if (*current_commande == NULL)
		*current_commande = new_node;
	else
	{
		temp = create_temp_buffer((*current_commande)->cmd, new_node->cmd);
		garbagge(FREE, (*current_commande)->cmd, PARS);
		garbagge(FREE, *current_commande, PARS);
		*current_commande = (t_cmd *)malloc(sizeof(t_cmd));
		if (!(*current_commande) || garbagge(ADD, *current_commande, PARS))
			return (perror("Memory allocation error"), exit(EXIT_FAILURE),
				(void)0);
		(*current_commande)->cmd = temp;
		(*current_commande)->next = NULL;
	}
}

void creation_cmd_empty(t_cmd **current_commande, const char *new_cmd)
{
    t_cmd	*new_node;
	t_cmd	*temp;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node || garbagge(ADD, new_node, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
    new_node->next = NULL;
    if (new_cmd)
    {
        new_node->cmd = ft_strdup(new_cmd);
        if (!new_node->cmd || garbagge(ADD, new_node->cmd, PARS))
			(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
    }
    else
        new_node->cmd = NULL;
    if (*current_commande == NULL)
        *current_commande = new_node;
    else
    {
        temp = *current_commande;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}

int	is_current_command_empty(t_cmd *current_command)
{
	return (current_command == NULL);
}

void	add_command_to_list_token(t_cmd **command_list, t_cmd *command)
{
	t_cmd	*temp_list;

	if (!*command_list)
		*command_list = command;
	else
	{
		temp_list = *command_list;
		while (temp_list->next)
			temp_list = temp_list->next;
		temp_list->next = command;
	}
}

void handle_pipe_case(t_cmd *temp, t_cmd *prev_temp, t_cmd *command_list)
{
    t_cmd *next_temp;
	t_cmd *empty_command;

	next_temp = temp->next;
    if (!prev_temp || (prev_temp && ft_strcmp(temp->cmd, "|") == 0
		&& ft_strcmp(prev_temp->cmd, "|") == 0))
    {
        empty_command = NULL;
        creation_cmd_empty(&empty_command, NULL);
        add_command_to_list_token(&command_list, empty_command);
    }
    if (!next_temp)
    {
        empty_command = NULL;
        creation_cmd_empty(&empty_command, NULL);
        add_command_to_list_token(&command_list, empty_command);
    }
}

t_cmd	*loop_p_for_token(t_cmd *command_list, t_cmd *temp, t_cmd *prev_temp, t_cmd *current_command)
{
	while (temp)
	{
		if (ft_strcmp(temp->cmd, "|") != 0 && temp->cmd)
		{
			creation_cmd(&current_command, temp->cmd);
			prev_temp = temp;
			temp = temp->next;
			if (!temp || (temp && ft_strcmp(temp->cmd, "|") == 0))
			{
				add_command_to_list_token(&command_list, current_command);
				current_command = NULL;
			}
			continue ;
		}
		else
			handle_pipe_case(temp, prev_temp, command_list);
		prev_temp = temp;
        temp = temp->next;
	}
	return (command_list);
}

t_cmd *parse_for_token(t_cmd *to_pars)
{
	t_cmd	*command_list;
	t_cmd	*temp;
	t_cmd	*prev_temp;
	t_cmd	*current_command;

	temp = to_pars;
	command_list = NULL;
	prev_temp = NULL;
	current_command = NULL;
	command_list = loop_p_for_token(command_list,
			temp, prev_temp, current_command);
	return (command_list);
}


void	commande_print(char **commande_split)
{
	int	i;

	i = -1;
	if (commande_split)
	{
		while (commande_split[++i])
			printf("commande split %d -> %s\n", i, commande_split[i]);
	}
	return ;
}

void	print_string_array(char **str_array)
{
	if (str_array == NULL)
	{
		printf("Array is NULL\n");
		return ;
	}
	for (int i = 0; str_array[i] != NULL; ++i)
	{
		printf("good_commande %s\n", str_array[i]);
	}
}



void	print_file_list(t_file *head)
{
	t_file	*current;

	current = head;
	while (current != NULL)
	{
		printf("redir: %s, nome_file: %s\n", current->redir,
				current->nome_file);
		current = current->next;
	}
}

int	get_file_list_array_size(t_file ***file)
{
	int	size;

	size = 0;
	while (file[size] != NULL)
		size++;
	return (size);
}


char	*change_in_quotes_espace(char *cmd, char replacement)
{
	int		i;
	int		inside_quotes;

	i = 0;
	inside_quotes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			inside_quotes = !inside_quotes;
		else if (inside_quotes && cmd[i] == '*')
			cmd[i] = replacement;
		i++;
	}
	return (cmd);
}

void	close_if_plus_zero(t_execve *pipex)
{
	close(pipex->tmp_fd[pipex->current_pipe][0]);
	close(pipex->tmp_fd[pipex->current_pipe][1]);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

void	pass_execve(char **good_commande, char *get_good_path, t_execve *pipex, int i)
{
	if (i)
	{
		garbagge(FLUSH, NULL, ALL);
		exit(1);
	}
	if (execve(get_good_path, good_commande, pipex->new_enviroment) == - 1)
	{
		perror("execve error");
		garbagge(FLUSH, NULL, ALL);
		exit(1);
	}
}

void	found_echo_in_pipe(t_cmd *new_to_pars)
{
	char	*echo;
	char	*cmd;
	int		count;

	echo = ft_substr(new_to_pars->cmd, 5, ft_strlen(new_to_pars->cmd));
	if (!echo || garbagge(ADD, echo, PARS))
		return (garbagge(FLUSH, NULL, ALL),exit(1));
	count = ft_strl(echo);
	cmd = malloc(count + 1);
	if (garbagge(ADD, cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	ft_strlcpy_msh(cmd, echo, count + 1, NULL);
	printf("%s\n", cmd);
	if (new_to_pars->next)
		printf(" ");
 	garbagge(FLUSH, NULL, ALL);
	exit(1); 
}

int        ft_check_valid_flag_echo(char *s) // MODIF GAGA
{
    int i;

    i = 0;
    if (s && s[i] == '-' && s[i + 1])
    {
        while (s[++i])
        {
            if (s[i] != 'n')
                return (1);
        }
        return (0);
    }
    return (1);
}

void    found_echo_in_pipe_flag(char **tmp) // MODIF GAGA
{
    int i;

    i = 0;
    while (tmp[i])
    {
        if (ft_check_valid_flag_echo(tmp[i]))
            break;
        i++;
    }
    while (tmp[i])
    {
        printf("%s", tmp[i]);
        if (tmp[i + 1])
            printf(" ");
        i++;
    }
    garbagge(FLUSH, NULL, ALL);
    exit(0);
}

// void	found_echo_in_pipe_flag(t_cmd *new_to_pars)
// {
// 	char	*echo;
// 	char	*cmd;
// 	int		count;
	
// 	echo = ft_substr(new_to_pars->cmd, 5, ft_strlen(new_to_pars->cmd));
// 	if (!echo || garbagge(ADD, echo, PARS))
// 		return (garbagge(FLUSH, NULL, ALL),exit(1));
// 	count = ft_strl(echo);
// 	cmd = malloc(count + 1);
// 	if (garbagge(ADD, cmd, PARS))
// 		(garbagge(FLUSH, NULL, ALL), exit(99));
// 	ft_strlcpy_msh(cmd, echo, count + 1, NULL);
// 	printf("%s", cmd);
// 	if (new_to_pars->next)
// 		printf(" ");
// 	garbagge(FLUSH, NULL, ALL);
// 	exit(1); 
// }

void	print_env_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array == NULL)
		return ;
	while(str_array[i])
	{
		printf("%s\n", str_array[i]);
		i++;
	}
}

const char *found_in_env_char(char **envi)
{
	int			i;
	const char	*f;

	i = -1;
	while (envi[++i])
	{
		f = ft_strnstr(envi[i], "PWD=", ft_strlen("PWD="));
		if (f)
			return (f);
	}
	return (NULL);
}

void	found_pwd_in_pipe(t_execve *pipex)
{
	const char	*pwd;

	pwd = found_in_env_char(pipex->new_enviroment);
	printf("%s\n", pwd);
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}


int	if_not_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (ft_isalpha(s[i]) || s[i] == '-')
			return (0);
		i++;
	}
	return (i);
}
void	print_err_to_not_numb(char *exit_r)
{
	ft_putstr_fd("bash: exit :", 2);
	ft_putstr_fd(exit_r, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	garbagge(FLUSH, NULL, ALL);
	exit(2);
}




void	found_exit_in_pipe(t_cmd *ntp)
{
	char	**exit_n;
	int		n;

	n = 0;
	exit_n = ft_split_garbage(ntp->cmd, ' ');
	if (!exit_n)
		exit(99);
	if (exit_n[1])
	{
		if (exit_n[2])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			garbagge(FLUSH, NULL, ALL);
			exit(2);
		}
		if (check_for_max_int(exit_n[1]))
			print_err_to_not_numb(exit_n[1]);
		if (!if_not_numeric(exit_n[1]))
			print_err_to_not_numb(exit_n[1]);
		n = ft_atoi(exit_n[1]);
		garbagge(FLUSH, NULL, ALL);
		exit((256 + n) % 256);
	}
	garbagge(FLUSH, NULL, ALL);
	exit(0);
}

void	found_export_in_pipe(char *cmd, t_execve *pipe)
{
	char	*error;

	error = ft_substr(cmd, 4, ft_strlen(cmd));
	if (!error || garbagge(ADD, error, EX))
		return ;
	if (!ft_strcmp(cmd, "export"))
		print_env_array(pipe->exp);
	else if (!ft_strncmp(cmd, "export ", 4))
	{
		garbagge(FLUSH, NULL, ALL);
		exit(1);
	}
	garbagge(FLUSH, NULL, ALL);
	exit(1);
}


void	found_env_in_pipe(char *cmd, t_execve *pipe)
{
	char	*error;

	error = ft_substr(cmd, 4, ft_strlen(cmd));
	if (!error || garbagge(ADD, error, EX))
		return ;
	if (!ft_strcmp(cmd, "env"))
		print_env_array(pipe->new_enviroment);
	else if (!ft_strncmp(cmd, "env ", 4))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd(" :not such a file or directory\n", 2);
	}
	garbagge(FLUSH, NULL, ALL);
	exit(1);
}

void    child_check_path_ifnt_error(t_cmd *new_to_pars, t_envp *enviroment, t_execve *pipex, char **tmp) // MODIF GAGA
{
	int    j;

    j = 0;
	if (tmp && tmp[0]
		&& ft_strcmp(tmp[0], "echo") // MODIF GAGA
		&& ft_strcmp(tmp[0], "env") // MODIF GAGA
		&& ft_strcmp(tmp[0], "export")
		&& ft_strcmp(tmp[0], "exit")
		&& ft_strcmp(tmp[0], "pwd")
		&& ft_strcmp(tmp[0], "cd")
		&& ft_strcmp(tmp[0], "unset"))
	{
        pipex->get_g_path = ft_good_path_access(new_to_pars, enviroment, pipex);
		if (!pipex->get_g_path)
		{
            j = ft_error_commande_not_to_pars(new_to_pars, pipex);
			if (j)
			{
				close(pipex->fd[0]);
				close(pipex->fd[1]);
				close(pipex->tmp_fd[pipex->current_pipe][0]);
				close(pipex->tmp_fd[pipex->current_pipe][1]);
				(garbagge(FLUSH, NULL, ALL), exit(j));
			}
		}
	}
}



// void	child_check_path_ifnt_error(t_cmd *new_to_pars, t_envp *enviroment, t_execve *pipex)
// {
// 	int	j;

// 	j = 0;
// 	if (new_to_pars && new_to_pars->cmd
// 		&& ft_strncmp(new_to_pars->cmd, "export ", ft_strlen("export"))
// 		&& ft_strncmp(new_to_pars->cmd, "\'export\' ", ft_strlen("\'export\'")) 
// 		&& ft_strncmp(new_to_pars->cmd, "exit ", ft_strlen("exit"))
// 		&& ft_strncmp(new_to_pars->cmd, "cd", ft_strlen("cd"))
// 		&& ft_strncmp(new_to_pars->cmd, "unset", ft_strlen("unset")))
// 	{
// 		pipex->get_g_path = ft_good_path_access(new_to_pars, enviroment, pipex);
// 		if (!pipex->get_g_path)
// 		{
// 			j = ft_error_commande_not_to_pars(new_to_pars, pipex);
// 			if (j)
// 			{
// 				close(pipex->fd[0]);
// 				close(pipex->fd[1]);
// 				close(pipex->tmp_fd[pipex->current_pipe][0]);
// 				close(pipex->tmp_fd[pipex->current_pipe][1]);
// 				(garbagge(FLUSH, NULL, ALL), exit(j));
// 			}
// 		}
// 	}
// }

void    built_in_child_execve(t_cmd *new_to_pars, t_execve *pipex, int j, t_envp *enviroment)
{
    char **tmp;
    
    tmp = NULL;
    if (new_to_pars && new_to_pars->cmd)
    {
        tmp = ft_split_garbage_gogo(new_to_pars->cmd, ' ');
        if (!tmp) // SECU A CHECKER AVEC NICO ( ne pas ajouter tmp au garbagge car split l a deja fait)
            (garbagge(FLUSH, NULL, ALL), exit (99)); // SECU A CHECKER AVEC NICO
    }
    child_check_path_ifnt_error(new_to_pars, enviroment, pipex, tmp);
    if (pipex->n_pipe - 1 > 0)
        close_if_plus_zero(pipex);
    if (tmp && tmp[0] && !ft_strcmp(tmp[0], "echo") && tmp[1] && !ft_check_valid_flag_echo(tmp[1]))
        found_echo_in_pipe_flag(tmp + 1);
    if (tmp && tmp[0] && !ft_strcmp(tmp[0], "echo"))
        found_echo_in_pipe(new_to_pars);
    if (tmp && tmp[0] && !ft_strcmp(tmp[0], "env"))
        found_env_in_pipe(new_to_pars->cmd, pipex);
    if (tmp && tmp[0] && !ft_strcmp(tmp[0], "export"))
        found_export_in_pipe(new_to_pars->cmd, pipex);
    if (tmp && tmp[0] && !ft_strcmp(tmp[0], "exit"))
        found_exit_in_pipe(new_to_pars);
    if (tmp && tmp[0] && !ft_strcmp(tmp[0], "pwd"))
        found_pwd_in_pipe(pipex);
    else if (!new_to_pars || !new_to_pars->cmd
        || !ft_strcmp(tmp[0], "unset")
        || !ft_strcmp(tmp[0], "cd"))
        (garbagge(FLUSH, NULL, ALL), exit(1));
    else
        pass_execve(pipex->good_cmd, pipex->get_g_path, pipex, j);
}

// void	built_in_child_execve(t_cmd *new_to_pars, t_execve *pipex, int j, t_envp *enviroment)
// {
// 	child_check_path_ifnt_error(new_to_pars, enviroment, pipex);
// 	if (pipex->n_pipe - 1 > 0)
// 		close_if_plus_zero(pipex);
// 	else if (new_to_pars->cmd && ft_strncmp(new_to_pars->cmd, "echo -n", ft_strlen("echo -n")) == 0)
// 		echo_flag_funny(new_to_pars, new_to_pars, pipex->error);
// 	if (new_to_pars && new_to_pars->cmd && new_to_pars->next
// 		&& (ft_strncmp(new_to_pars->cmd, "echo -n", ft_strlen("echo -n")) == 0))
// 		found_echo_in_pipe_flag(new_to_pars);
// 	if (new_to_pars && new_to_pars->cmd && new_to_pars->next
// 		&& (ft_strncmp(new_to_pars->cmd, "echo ", ft_strlen("echo ")) == 0))
// 		found_echo_in_pipe(new_to_pars);
// 	if (new_to_pars && new_to_pars->cmd 
// 		&& (!ft_strncmp(new_to_pars->cmd, "env ", ft_strlen("env"))))
// 		found_env_in_pipe(new_to_pars->cmd, pipex);
// 	if (new_to_pars && new_to_pars->cmd 
// 		&& (!ft_strncmp(new_to_pars->cmd, "export ", ft_strlen("export"))))
// 		found_export_in_pipe(new_to_pars->cmd, pipex);
// 	if (new_to_pars && new_to_pars->cmd
// 		&& (!ft_strncmp(new_to_pars->cmd, "exit", ft_strlen("exit"))))
// 		found_exit_in_pipe(new_to_pars);
// 	if (new_to_pars && new_to_pars->cmd
// 		&& (ft_strncmp(new_to_pars->cmd, "pwd", ft_strlen("pwd")) == 0))
// 		found_pwd_in_pipe(pipex);
// 	else if (!new_to_pars || !new_to_pars->cmd
// 		|| !ft_strncmp(new_to_pars->cmd, "unset", ft_strlen("unset"))
// 		|| !ft_strncmp(new_to_pars->cmd, "cd", ft_strlen("cd")))
// 		(garbagge(FLUSH, NULL, ALL), exit(1));
// 	else
// 		pass_execve(pipex->good_cmd, pipex->get_g_path, pipex, j);
// }


void	child(t_cmd *new_to_pars, t_execve *pipex, int i, t_envp *enviroment)
{
	char	*tmp;

	if (new_to_pars && new_to_pars->cmd)
	{
		tmp = ft_strdup(new_to_pars->cmd);
		if (!tmp || garbagge(ADD, tmp, PARS))
			return ((void)0);
		pipex->good_cmd = ft_split_garbage_gogo(new_to_pars->cmd, ' ');
		if (!pipex->good_cmd)
			return (perror("error split"), (void)0);
	}
	redirection(pipex->fd, pipex->current_pipe, pipex);
	built_in_child_execve(new_to_pars, pipex, i, enviroment);
}

void	parent(int *fd, int i, t_execve *pipex)
{
	if (i > 0)
	{
		close(pipex->tmp_fd[i - 1][0]);
		close(pipex->tmp_fd[i - 1][1]);
	}
	if (i < pipex->n_pipe - 1)
		close(fd[1]);
	if (pipex->n_pipe - 1 > 0)
	{
		close(fd[1]);
		close(fd[0]);
	}
}

int	found_in_to_pars(t_cmd *current)
{
	if (ft_strncmp(current->cmd, "<", 1) == 0
		|| ft_strncmp(current->cmd, ">", 1) == 0
		|| ft_strncmp(current->cmd, ">>", 2) == 0 || ft_strncmp(current->cmd,
			"<<", 2) == 0)
		return (0);
	return (1);
}

t_cmd	*add_redirection_to_list(t_cmd **new_list_ptr, t_cmd *prev,
		t_cmd *current)
{
	t_cmd	*new_commande;

	new_commande = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_commande || garbagge(ADD, new_commande, PARS))
	{
		perror("malloc failure");
		return (NULL);
	}
	new_commande->cmd = ft_strdup(current->cmd);
	if (!new_commande->cmd || garbagge(ADD, new_commande->cmd, PARS))
	{
		garbagge(FREE, new_commande, PARS);
		return (NULL);
	}
	new_commande->next = NULL;
	if (prev != NULL)
		prev->next = new_commande;
	else
		*new_list_ptr = new_commande;
	return (new_commande);
}

t_cmd	*remove_redirections(t_cmd *to_pars)
{
	t_cmd	*new_list;
	t_cmd	*prev;
	t_cmd	*new_commande;
	t_cmd	*current;

	new_list = NULL;
	current = to_pars;
	prev = NULL;
	while (current)
	{
		if (!found_in_to_pars(current))
		{
			if (current->next != NULL && current->next->cmd != NULL)
				current = current->next->next;
			else
				current = current->next;
		}
		else
		{
			new_commande = add_redirection_to_list(&new_list, prev, current);
			prev = new_commande;
			current = current->next;
		}
	}
	return (new_list);
}







/* 	// else if (ft_strncmp(to_pars->cmd, "<<", 2) == 0 && !to_pars->next)
	// {
	// 	char *here_dod = ft_substr(to_pars->cmd, 2, ft_strlen(to_pars->cmd));
	// 	if(!here_dod || garbagge(ADD,here_dod, EX))
	// 		return (garbagge(FLUSH, NULL, ALL), exit(1), 0);
	// 	sign = add_file_node_special(file_list, to_pars, here_dod,
	// 			enviroment);
	// }
	// else if (ft_strncmp(to_pars->cmd, ">>", 2) == 0 && !to_pars->next)
	// 	add_file_node_special(file_list, to_pars, NULL, enviroment);
	// else if (ft_strncmp(to_pars->cmd, "<", 1) == 0 && !to_pars->next)
	// 	add_file_node_special(file_list, to_pars, NULL, enviroment);
	// else if (ft_strncmp(to_pars->cmd, ">", 1) == 0 && !to_pars->next)
	// 	add_file_node_special(file_list, to_pars, NULL, enviroment);
	// else if (ft_strncmp(to_pars->cmd, "<<", 2) == 0 && to_pars->next)
	// {
	// 	char *here_dod = ft_substr(to_pars->cmd, 2, ft_strlen(to_pars->cmd));
	// 	if(!here_dod || garbagge(ADD, here_dod, EX))
	// 		return (garbagge(FLUSH, NULL, ALL), exit(1), 0);
	// 	sign = add_file_node_special(file_list, to_pars, here_dod,
	// 			enviroment);
	// }
	// else if (ft_strncmp(to_pars->cmd, ">>", 2) == 0 && to_pars->next)
	// 	add_file_node_special(file_list, to_pars, NULL, enviroment);
	// else if (ft_strncmp(to_pars->cmd, "<", 1) == 0 && to_pars->next)
	// 	add_file_node_special(file_list, to_pars, NULL, enviroment);
	// else if (ft_strncmp(to_pars->cmd, ">", 1) == 0 && to_pars->next)
	// 	add_file_node_special(file_list, to_pars, NULL, enviroment); */






void	postfork_ms_sig(int signal)
{
	(void)signal;
}

void	ms_signals(void)
{
	signal(SIGINT, postfork_ms_sig);
	signal(SIGQUIT, postfork_ms_sig);
}

void	logic_parent(t_execve *pipex, t_file **temp)
{
	ms_signals();
	parent(pipex->fd, pipex->current_pipe, pipex);
	if (pipex->pipe_redirections)
	{
		temp = pipex->pipe_redirections[pipex->current_pipe];
		if (*temp && *temp)
			*temp = (*temp)->next;
		else
			*temp = NULL;
	}
}


void	in_logic_fork(t_cmd *new_to_pars, t_execve *pipex, t_file **temp, int i, t_envp *enviroment)
{
	if (pipex->pid[pipex->current_pipe] == -1)
		perror("fork error");
	if (pipex->pid[pipex->current_pipe] == 0)
	{
		set_signal_action(3);
		child(new_to_pars, pipex, i, enviroment);
	}
	else
		logic_parent(pipex, temp);
}

int	execute_pipeline_command(t_execve *pipex, t_cmd *new_to_pars,
	t_envp *enviroment)
{
	t_file	**temp;
	int		i;

	i = 0;
	temp = NULL;
	if (pipex->n_pipe - 1 > 0)
	{
		if ((pipe(pipex->fd) == -1
				|| pipe(pipex->tmp_fd[pipex->current_pipe]) == -1))
			perror("pipe error");
	}
	pipex->pid[pipex->current_pipe] = fork();
	in_logic_fork(new_to_pars, pipex, temp, i, enviroment);
	return (i);
}

void    logic_wait_pd(t_execve *pipex, int n)
{
	int		status;
	int		i;

	i = 0;
	if (!pipex)
		return ;
	while (i < pipex->n_pipe - n && pipex->pid[i])
	{
		if (waitpid(pipex->pid[i], &status, 0) == -1)
			perror("waitpid error");
		else
		{
			if (WIFEXITED(status))
				pipex->error = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				pipex->error = WTERMSIG(status) + 128;
				if (pipex->error == 130)
					printf("\n");
				if (pipex->error == 131)
					printf("Quit (core dumped)\n");
			}
		}
		i++;
	}
}


void	close_if_open(int fd)
{
	if (fd != -1)
		close(fd);
}

void	close_all_fd_tmp(t_execve *pipex, int n)
{
	if (!pipex)
		return ((void)0);
	pipex->current_pipe = 1;
	while (pipex->current_pipe < pipex->n_pipe - n
		&& pipex->pid[pipex->current_pipe])
	{
		close(pipex->tmp_fd[pipex->current_pipe][1]);
		close(pipex->tmp_fd[pipex->current_pipe][0]);
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		pipex->current_pipe++;
	}
}

void	found_quotes(t_cmd *to_pars)
{
	char	*trimmed;
	char	*cmd;

	while (to_pars)
	{
		cmd = to_pars->cmd;
		trimmed = ft_strtrim(cmd, "\"");
		if (!trimmed || garbagge(ADD, trimmed, EX))
			return ((void)0);
		to_pars->cmd = trimmed;
		to_pars = to_pars->next;
	}
}

void	found_single_quotes(t_cmd *to_pars)
{
	char	*trimmed;
	char	*cmd;

	while (to_pars)
	{
		cmd = to_pars->cmd;
		trimmed = ft_strtrim(cmd, "\'");
		if (!trimmed || garbagge(ADD, trimmed, EX))
			return ((void)0);
		to_pars->cmd = trimmed;
		to_pars = to_pars->next;
	}
}

void add_node_sp(t_cmd **head_ref, char *cmd)
{
	t_cmd *new_node;
	t_cmd *last;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->cmd = cmd;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}




// Conta gli spazi prima del token di redirezione
            // Conta gli spazi dopo il token di redirezione
            // Se ci sono al massimo 3 spazi prima e dopo il token di redirezione
            // e se c'è un'altra redirezione dello stesso tipo subito dopo

// void remove_spaces_after_redirect(char *str, int index, int *len)
// {
    // int spaces_after = 0;
    // int j = index + 1;
    // Conta gli spazi dopo il token di redirezione
    // while (str[j] == ' ')
    // {
        // spaces_after++;
        // j++;
    // }
// 
    // Rimuovi gli spazi dopo il token di redirezione
    // if (spaces_after > 0)
    // {
        // ft_memmove(str + index + 1, str + index + 1 + spaces_after, *len - index - spaces_after + 1);
        // *len -= spaces_after;
    // }
// }

void count_spaces_before_and_after(char *str, int index, t_for_re *re)
{
	int j;

    re->spaces_before = 0;
    re->spaces_after = 0;
    re->j_after_count = index + 1;
    j = index - 1;
    while (j >= 0 && str[j] == ' ')
    {
        (re->spaces_before)++;
        j--;
    }
    j = index + 1;
    while (str[j] == ' ')
    {
        (re->spaces_after)++;
        j++;
    }
    re->j_after_count = j;
}

t_for_re	*init_esp(char *cmd)
{
	t_for_re	*esp;

	esp = (t_for_re*)malloc(sizeof(t_for_re));
	if (!esp || garbagge(ADD, esp, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	esp->len = ft_strlen(cmd);	
	esp->j_after_count = 0;
	esp->spaces_after = 0;
	esp->spaces_before = 0;
	return (esp);
}

char *check_redir_for_split(char *cmd)
{
	char		*result;
    int			i;
	t_for_re	*esp;

	esp = init_esp(cmd);
    result = (char *)malloc((esp->len + 2) * sizeof(char));
	if (!result || garbagge(ADD, result, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
	ft_strcpy(result, cmd, ft_strlen(cmd) + 1);
	i = -1;
	while (result[++i])
	{
		if (result[i] == '<' || result[i] == '>')
		{
			count_spaces_before_and_after(result, i, esp);
			if (esp->spaces_before <= 3 && esp->spaces_after <= 3
				&& (result[esp->j_after_count] == '<'
					|| result[esp->j_after_count] == '>'))
			{
				ft_memmove(result + i + 1, result + i + 1 + esp->spaces_after
					, esp->len - i - esp->spaces_after + 1);
				esp->len -= esp->spaces_after;
			}
		}
	}
	return (result);
}

void add_spaces_around_token(char *token, char **new_token, char *last_char) // MODIF GAGA
{
	if (*last_char != -1 && *last_char != ' '
		&& *last_char != '"' && *last_char != '\'')
	    *(*new_token)++ = ' ';
	*(*new_token)++ = *token;
	if ((*(token + 1) != ' ' && *(token + 1) != '\0'
		&& *(token + 1) != '"' && *(token + 1) != '\'')
	    && (*token == '<' || *token == '>' || *token == '|'))
	    *(*new_token)++ = ' ';
	*last_char = *token;
}

char	*new_cmd_for_token(char *token)
{
	char	*new_com;

	new_com = (char *)malloc(ft_strlen(token) * 2 + 2);
	if (!new_com || garbagge(ADD, new_com, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(EXIT_FAILURE));
	return (new_com);
}

/* CHECK AVANT */

void add_ep_redirection_and_pipes(t_cmd *head) // MODIF GAGA
{
    t_cmd    *current;
    char    *new_com;
    char    *token;
    char    *new_token;
    char    last_char;

    current = head;
    last_char = -1;
    while (current)
    {
        token = current->cmd;
        new_com = new_cmd_for_token(token);
        new_token = new_com;
        while (*token)
        {
            if (*token == '<' || *token == '>' || *token == '|')
                add_spaces_around_token(token, &new_token, &last_char);
            else
                *new_token++ = *token;
            last_char = *token; // Aggiorna l'ultimo carattere aggiunto
            token++;
        }
        *new_token = '\0';
        current->cmd = check_redir_for_split(new_com);
        current = current->next;
    }
}



void	append_to_list_red(t_cmd **new_list, t_cmd *cmd)
{
	t_cmd *tail;

	tail = NULL;
	if (*new_list == NULL)
		*new_list = cmd;
    else
    {
        tail = *new_list;
        while (tail->next)
            tail = tail->next;
        tail->next = cmd;
    }
}


t_cmd *add_cmd_for_redir(t_cmd *list)
{
    t_cmd	*new_list; // Creare una nuova lista vuota
	int		i;
	char	**commande_split;
	t_cmd	*cmd;

	new_list = NULL;
    while (list != NULL)
    {
        i = -1;
        if (!list->cmd)
            return (NULL);
        commande_split = ft_split_garbage(list->cmd, ' ');
        if (!commande_split)
            return (NULL);
        while (commande_split[++i])
        {
            cmd = add_new_cmd(commande_split, i);
            if (!cmd)
                return (NULL);
			append_to_list_red(&new_list, cmd);
        }
        list = list->next;
    }
    return (new_list);
}


t_cmd *parsing_before_pipe_red(t_cmd *to_pars)
{
	t_cmd 	*cur;

	cur = to_pars;
	add_ep_redirection_and_pipes(cur);
	cur = add_cmd_for_redir(cur);
	return (cur);
}

int	brain_execute_pipe_command(t_cmd *new_to_pars, t_execve *pipex, t_envp *enviroment)
{
	int	n;

	n = 0;
	while ((pipex && pipex->current_pipe < pipex->n_pipe && new_to_pars)
		|| (pipex && pipex->current_pipe < pipex->n_pipe && new_to_pars
			&& pipex->pipe_redirections[pipex->current_pipe])
		|| (pipex && pipex->current_pipe < pipex->n_pipe && !new_to_pars
			&& pipex->pipe_redirections[pipex->current_pipe]))
	{
		if (execute_pipeline_command(pipex, new_to_pars, enviroment))
			n++;
		pipex->current_pipe++;
		if (new_to_pars && new_to_pars->next)
			new_to_pars = new_to_pars->next;
	}
	return (n);
}

t_cmd *copy_node(t_cmd *original)
{
    if (!original)
	{
        return NULL;
	}
    t_cmd *copy = (t_cmd *)malloc(sizeof(t_cmd));
	if(!copy || garbagge(ADD, copy, PARS))
        return NULL; // Gestione errore: malloc fallita
    copy->cmd = original->cmd; // Esempio, sostituisci "data" con il campo che contiene i dati
    copy->next = copy_node(original->next); // Copia il nodo successivo ricorsivamente
	return (copy);
}

int	len_liste_cmd(t_cmd *cmd)
{
	int	index;

	index = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		index++;
		cmd = cmd->next;
	}
	return (index + 1);
}

int	ft_execve(t_cmd *to_pars, t_envp *enviroment, t_exp *export, int error_status)
{
	t_execve	*pipex;
	t_cmd		*new_to_pars;
	int			n;

	n = 0;
	if (!to_pars)
		return (0);
	new_to_pars = parsing_before_pipe_red(to_pars);
	pipex = init_structure(enviroment, new_to_pars, export, error_status);
	if (!pipex)
		return (1);
	pipex->cmd_err = NULL;
	pipex->cmd_err = copy_node(to_pars);
	new_to_pars = remove_redirections(new_to_pars);
	new_to_pars = parse_for_token(new_to_pars);
	pipex->for_h = len_liste_cmd(new_to_pars);
	n = brain_execute_pipe_command(new_to_pars, pipex, enviroment);
	logic_wait_pd(pipex, n);
	close_all_fd_tmp(pipex, n);
	if (g_signal_received == 60)
		return (error_status);
	error_status = pipex->error;
	return (pipex->error);
}



int	found_infile_or_endfile(t_cmd *to_pars)
{
	while (to_pars)
	{
		if (ft_strncmp(to_pars->cmd, "<", ft_strlen("<")) == 0)
			return (1);
		if (ft_strncmp(to_pars->cmd, ">", ft_strlen(">")) == 0)
			return (2);
		if (ft_strncmp(to_pars->cmd, ">>",ft_strlen(">>")) == 0)
			return (3);
		if (ft_strncmp(to_pars->cmd, "<<",ft_strlen("<<")) == 0)
			return (4);
		to_pars = to_pars->next;
	}
	return (0);
}

char	*direction_in_out_file(t_cmd *to_pars)
{
	while (to_pars)
	{
		if (ft_strcmp(to_pars->cmd, "<") == 0)
			return (to_pars->next->cmd);
		if (ft_strcmp(to_pars->cmd, ">") == 0)
			return (to_pars->next->cmd);
		if (ft_strcmp(to_pars->cmd, ">>") == 0)
			return (to_pars->next->cmd);
		if (ft_strcmp(to_pars->cmd, "<<") == 0)
			return (to_pars->next->cmd);
		to_pars = to_pars->next;
	}
	return (NULL);
}
