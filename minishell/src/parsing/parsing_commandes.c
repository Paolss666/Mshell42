/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commandes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:11:47 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/11 22:49:39 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		g_signal_received = 0;

int	ft_check_only_quote(char *line)
{
	int		i;
	t_quote	q;

	i = 0;
	q.d_q = 0;
	q.s_q = 0;
	while (line[i])
	{
		if (line[i] != '\'' && line[i] != '"')
			return (1);
		else
			ft_inc_quote(line[i], &q.d_q, &q.s_q);
		i++;
	}
	if (q.d_q % 2 == 0 && q.s_q % 2 == 0)
		return (0);
	return (1);
}

char	*display_prompt(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(COLOR_RED "Mshell$ " RESET_COLOR);
		if (!line || garbagge(ADD, line, PARS))
			return (NULL);
		if (!line[0])
		{
			garbagge(FREE, line, PARS);
			line = NULL;
			continue ;
		}
		if (line)
			add_history(line);
		return (line);
	}
}

char	*init_for_join_found_flag(t_cmd *next, t_cmd *current)
{
	char	*espace;
	char	*temp_cmd;

	espace = ft_strjoin(" ", next->cmd);
	if (!espace || garbagge(ADD, espace, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	temp_cmd = ft_strjoin(current->cmd, espace);
	if (!temp_cmd || garbagge(ADD, temp_cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	return (temp_cmd);
}

int	join_found_flag(t_cmd **to_pars)
{
	t_cmd	*current;
	t_cmd	*next;
	int		count;

	next = NULL;
	count = 0;
	current = *to_pars;
	if (!*to_pars)
		return (0);
	while (current != NULL && current->cmd != NULL)
	{
		next = current->next;
		while (next != NULL && next->cmd != NULL && next->cmd[0] == '-')
		{
			current->cmd = init_for_join_found_flag(next, current);
			current->next = next->next;
			next = current->next;
		}
		count++;
		current = current->next;
	}
	return (count);
}

/* --->>>>> toutes les commandes mis dans les listes chainees <<-------- */
void	ft_free_tab_garbage(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		garbagge(FREE, tab[i], PARS);
	garbagge(FREE, tab, PARS);
}

t_cmd	*add_new_cmd(char **commande_split, int i)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd || garbagge(ADD, cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	cmd->cmd = ft_strdup(commande_split[i]);
	if (!cmd->cmd || garbagge(ADD, cmd->cmd, PARS))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	cmd->count = 0;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*add_cmd_star(t_cmd *list, char *line)
{
	t_cmd	*cmd;
	t_cmd	*current;
	int		i;
	char	**commande_split;

	i = -1;
	if (!line)
		return (NULL);
	commande_split = ft_split_garbage(line, '\v');
	if (!commande_split)
		return (ft_free_tab_garbage(commande_split), NULL);
	while (commande_split[++i])
	{
		cmd = add_new_cmd(commande_split, i);
		if (!list)
			list = cmd;
		else
		{
			current = list;
			while (current->next)
				current = current->next;
			current->next = cmd;
		}
	}
	return (list);
}

t_cmd	*add_cmd_list(t_cmd *list, char **commande_split, char *line)
{
	t_cmd	*cmd;
	t_cmd	*current;
	int		i;

	i = -1;
	if (!commande_split)
	{
		commande_split = ft_split_garbage(line, ' ');
		if (!commande_split)
			return (ft_free_tab_garbage(commande_split), NULL);
	}
	while (commande_split[++i])
	{
		cmd = add_new_cmd(commande_split, i);
		if (!list)
			list = cmd;
		else
		{
			current = list;
			while (current->next)
				current = current->next;
			current->next = cmd;
		}
	}
	return (list);
}

void	free_list_to_pars(t_cmd **to_pars)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *to_pars;
	while (current)
	{
		next = current->next;
		if (current->cmd)
			garbagge(FREE, current->cmd, PARS);
		garbagge(FREE, current, PARS);
		current = next;
	}
	*to_pars = NULL;
}

int	len_liste_exp(t_exp *enviromet)
{
	int	index;

	index = 0;
	if (!enviromet)
		return (0);
	while (enviromet)
	{
		index++;
		enviromet = enviromet->next;
	}
	return (index + 1);
}

int	len_liste_envp(t_envp *enviromet)
{
	int	index;

	index = 0;
	if (!enviromet)
		return (0);
	while (enviromet)
	{
		index++;
		enviromet = enviromet->next;
	}
	return (index + 1);
}

int	found_token(t_cmd *to_pars)
{
	while (to_pars)
	{
		if (ft_strcmp(to_pars->cmd, "export") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "unset") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "echo") == 0)
			return (1);
		if (ft_strncmp(to_pars->cmd, "echo -", 6) == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "env") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "cd") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "cd -") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "exit") == 0)
			return (1);
		if (ft_strncmp(to_pars->cmd, "exit -", ft_strlen("exit -")) == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "pwd") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

int	found_pwd(t_cmd *to_pars)
{
	while (to_pars)
	{
		if (ft_strcmp(to_pars->cmd, "pwd") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

char	*found_path_envp_list(t_envp *enviroment)
{
	char	*env_path;

	env_path = NULL;
	if (!enviroment)
		return (NULL);
	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "PATH") == 0)
		{
			env_path = ft_strdup(enviroment->path);
			if (!env_path || garbagge(ADD, env_path, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			else
				return (env_path);
		}
		enviroment = enviroment->next;
	}
	return (NULL);
}

int	found_level(t_cmd *to_pars)
{
	t_cmd	*current;

	current = to_pars;
	if (!to_pars)
		return (0);
	while (current)
	{
		if (ft_strcmp(current->cmd, "./minishell") == 0)
			return (1);
		if (ft_strcmp(current->cmd, "bash --posix") == 0)
			return (1);
		if (ft_strcmp(current->cmd, "bash") == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	logic_found_shlvl_env(t_envp *enviroment)
{
	int		n;
	char	*tmp;

	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "SHLVL") == 0)
		{
			n = ft_atoi(enviroment->value) + 1;
			enviroment->value = ft_itoa(n);
			if (!enviroment->value || garbagge(ADD, enviroment->value, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			tmp = ft_strjoin(enviroment->name, "=");
			if (!tmp || garbagge(ADD, tmp, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			enviroment->path = ft_strjoin(tmp, enviroment->value);
			if (!enviroment->path || garbagge(ADD, enviroment->path, ENV))
				(garbagge(FLUSH, NULL, ALL), exit(99));
			garbagge(FREE, tmp, ENV);
			return ;
		}
		enviroment = enviroment->next;
	}
	return ;
}

void	change_in_exp(t_exp *export)
{
	int		n;
	char	*temp;
	char	*temp1;
	char	*final;

	export->value = ft_strchr(export->path, '=') + 1;
	export->name = ft_strdup("export SHLVL=\"");
	if (!export->name || garbagge(ADD, export->name, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	temp1 = ft_strtrim(export->value, "\"");
	if (!temp1 || garbagge(ADD, temp1, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	n = ft_atoi(temp1) + 1;
	temp = ft_itoa(n);
	if (!temp || garbagge(ADD, temp, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	final = ft_strjoin(temp, "\"");
	if (!final || garbagge(ADD, final, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
	export->path = ft_strjoin(export->name, final);
	if (!export->path || garbagge(ADD, export->path, ENV))
		(garbagge(FLUSH, NULL, ALL), exit(99));
}

void	logic_found_shlvl_expo(t_exp *export)
{
	while (export)
	{
		if (ft_strncmp(export->path, "export SHLVL=",
				ft_strlen("export SHLVL=")) == 0)
		{
			change_in_exp(export);
			return ;
		}
		export = export->next;
	}
}

void	found_shlv(t_envp *enviroment, t_exp *export)
{
	if (!enviroment || !export)
		return ;
	logic_found_shlvl_env(enviroment);
	logic_found_shlvl_expo(export);
	return ;
}

void	replace_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			str[i] = '\v';
		}
		i++;
	}
}

char	*return_exec(char *exec, char **with_flag, char **env_split)
{
	if (access(exec, F_OK | X_OK) == 0)
		return (ft_free_tab_garbage(with_flag), ft_free_tab_garbage(env_split),
			exec);
	return (NULL);
}

char	*check_path_absolut(char **with_flag, t_execve *pipex, int *dir)
{
	if (is_directory(with_flag[0]))
		return (*dir = 1, NULL);
	if (access(with_flag[0], F_OK | X_OK) == 0)
		return (with_flag[0]);
	if (access(with_flag[0], F_OK | X_OK) == -1)
	{
		(void)pipex;
		return (NULL);
	}
	return (NULL);
}

void	f_gbgb(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		garbagge(FREE, tab[i], PARS);
	garbagge(FREE, tab, PARS);
}

void	ft_init_var_0(int *i, int *dir)
{
	*i = -1;
	*dir = 0;
}

char	*logic_get_good_path(char **with_flag, char **env_split,
		t_execve *pipex)
{
	char	*exec;
	char	*try_line;
	int		i;
	int		dir;

	ft_init_var_0(&i, &dir);
	if (check_path_absolut(with_flag, pipex, &dir))
		return (with_flag[0]);
	if (dir == 1)
		return (NULL);
	while (env_split[++i])
	{
		try_line = ft_strjoin(env_split[i], "/");
		if (!try_line || garbagge(ADD, try_line, ENV))
			return (f_gbgb(with_flag), f_gbgb(env_split), NULL);
		exec = ft_strjoin(try_line, with_flag[0]);
		if (!exec || garbagge(ADD, exec, ENV))
			return (NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (f_gbgb(with_flag), f_gbgb(env_split), exec);
		if (access(exec, F_OK | X_OK) == -1 && pipex)
			pipex->error = 0;
		garbagge(FREE, exec, ENV);
	}
	return (NULL);
}

int	contains_only_spaces(const char *str)
{
	if (*str == ' ' && *(str + 1) == '\0')
		return (0);
	while (*str != '\0')
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

char	*ft_good_path_access(t_cmd *to_pars, t_envp *enviroment,
		t_execve *pipex)
{
	char	**env_split;
	char	**with_flag;
	char	*found_in_env;
	char	*tmp;

	tmp = ft_strdup(to_pars->cmd);
	if (!tmp || garbagge(ADD, tmp, PARS))
		return (NULL);
	found_in_env = NULL;
	env_split = NULL;
	with_flag = ft_split_garbage_gogo(to_pars->cmd, ' ');
	if (!with_flag || !with_flag[0] || with_flag[0][0] == '\0')
		return (NULL);
	if ((tmp[0] == '\'' && ft_strlen(tmp) == 1) || (tmp[0] == '\"'
			&& ft_strlen(tmp) == 1))
		return (NULL);
	found_in_env = found_path_envp_list(enviroment);
	if (!found_in_env)
		return (NULL);
	env_split = ft_split_garbage(found_in_env + 5, ':');
	if (!env_split)
		return (ft_free_tab_garbage(with_flag), NULL);
	if (with_flag[0])
		return (logic_get_good_path(with_flag, env_split, pipex));
	return (NULL);
}

char	**envp_list_to_new_env(t_envp *enviroment)
{
	char	**new_enviroment;
	int		i;

	i = 0;
	new_enviroment = (char **)malloc(sizeof(char *) * len_liste_envp(enviroment)
			+ 1);
	if (!new_enviroment || garbagge(ADD, new_enviroment, ENV))
		return (NULL);
	if (!enviroment || len_liste_envp(enviroment) <= 0)
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

int	count_single_quotes(char *cmd)
{
	int	c;
	int	i;

	c = 0;
	i = -1;
	while (cmd[++i])
		if (cmd[i] == '\'')
			c++;
	if (c == 0)
		return (1);
	else if (c % 2 == 0)
		return (0);
	return (1);
}

void	logic_expand_variable(int i, t_envp *enviroment, t_cmd *current,
		int e_st)
{
	char	*new_cmd;

	new_cmd = logic_print_variable(i, enviroment, current, e_st);
	if (new_cmd)
	{
		if (ft_strcmp(new_cmd, " ") == 0)
			new_cmd = NULL;
		else
		{
			if (new_cmd)
			{
				current->cmd = ft_strdup(new_cmd);
				if (!current->cmd || garbagge(ADD, current->cmd, PARS))
					return ((void)0);
				garbagge(FREE, new_cmd, PARS);
			}
			garbagge(FREE, new_cmd, PARS);
		}
	}
	new_cmd = NULL;
}

int	has_both_quotes(const char *str)
{
	int	sngl;
	int	db;
	int	i;

	sngl = 0;
	db = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sngl = 1;
		else if (str[i] == '"')
			db = 1;
		if (sngl && db)
			return (1);
		i++;
	}
	return (0);
}

int	logic_check_type_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (has_both_quotes(str))
			return (4);
		if ((str[i] == '\'' && (str[i + 1] == '\v' || str[i + 1] == '\0'
				|| is_valid_variable_char(str[i + 1]))))
			return (2);
		if (str[i] == '\"' && (str[i + 1] == '\v' || str[i + 1] == '\0'))
			return (3);
		i++;
	}
	return (0);
}

int	logic_found_dollar_interrogation(t_cmd *current, int error_status)
{
	if (ft_strcmp(current->cmd, "$?") == 0 && !current->next)
	{
		garbagge(FREE, current->cmd, PARS);
		current->cmd = ft_itoa(error_status);
		if (!current->cmd || garbagge(ADD, current->cmd, PARS))
			return (1);
		return (1);
	}
	return (0);
}

char	*ft_strndup_g(const char *src, size_t n)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	if (n < len)
		len = n;
	dest = (char *)malloc(len + 2);
	if (!dest || garbagge(ADD, dest, PARS))
		return (NULL);
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}

int	count_quotes_f_spl(const char *str)
{
	int		count;
	char	quote;

	count = 0;
	quote = '\0';
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == '\0')
				quote = *str;
			else if (*str == quote)
			{
				quote = '\0';
				count++;
			}
		}
		str++;
	}
	return (count);
}

void	process_token(const char *start, const char *end, char *tokens[],
		int *i)
{
	size_t	len;

	tokens[*i] = ft_strndup_g(start, end - start);
	if (!tokens[*i])
		(garbagge(FLUSH, NULL, ALL), exit(99));
	len = ft_strlen(tokens[*i]);
	tokens[*i][len] = *end;
	tokens[*i][len + 1] = '\0';
	(*i)++;
}

int	split_quotes(const char *str, char *tokens[])
{
	int			i;
	const char	*start;
	int			in_quote;

	start = str;
	in_quote = 0;
	i = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (!in_quote)
				start = str;
			else if (start && str)
			{
				process_token(start, str, tokens, &i);
				start = str + 1;
			}
			in_quote = !in_quote;
		}
		str++;
	}
	return (i);
}

char	*logic_sgl_q(char *joined, char *split)
{
	if (joined)
	{
		joined = ft_strjoin(joined, split);
		if ((!joined || garbagge(ADD, joined, PARS)))
			(garbagge(FLUSH, NULL, ALL), exit(99));
	}
	else
	{
		joined = ft_strdup(split);
		if ((!joined || garbagge(ADD, joined, PARS)))
			(garbagge(FLUSH, NULL, ALL), exit(99));
	}
	return (joined);
}

char	*ft_found_all_qo(char **split, int r_st, t_envp *env)
{
	char	*joined;
	int		j;

	j = 0;
	joined = NULL;
	while (split[j])
	{
		if (j == 0)
		{
			if (joined)
			{
				joined = ft_strjoin(joined, ft_expand_value(split[j], 1, env,
							r_st));
				if ((!joined || garbagge(ADD, joined, PARS)))
					(garbagge(FLUSH, NULL, ALL), exit(99));
			}
			else
				joined = ft_expand_value(split[j], 1, env, r_st);
		}
		else
			joined = logic_sgl_q(joined, split[j]);
		j++;
	}
	return (joined);
}

char	*exp_in_all_quotes(t_cmd *current, t_envp *environment, int r_st)
{
	char	*cmd;
	char	**split;

	split = ft_split_garbage_gogo_quote(current->cmd, ' ');
	cmd = ft_found_all_qo(split, r_st, environment);
	garbagge(FREE, current->cmd, PARS);
	return (cmd);
}

void	logic_exp_quotes(int r_st, int i, t_envp *environment, t_cmd *current)
{
	if (logic_check_type_quotes(current->cmd) == 4
		|| logic_check_type_quotes(current->cmd) == 2)
		current->cmd = exp_in_all_quotes(current, environment, r_st);
	if (logic_check_type_quotes(current->cmd) == 3)
	{
		if (current->cmd && ft_strchr(current->cmd, '$'))
			logic_expand_variable(i, environment, current, r_st);
	}
	else if (logic_check_type_quotes(current->cmd) == 0)
	{
		if (current->cmd && !ft_strcmp(current->cmd, "$?"))
			logic_found_dollar_interrogation(current, r_st);
		if (current->cmd && ft_strchr(current->cmd, '$'))
			logic_expand_variable(i, environment, current, r_st);
	}
}

t_cmd	*expand_dollar(t_cmd **to_pars, t_envp *environment, int error_status)
{
	int		i;
	t_cmd	*current;
	t_cmd	*prev;

	i = 1;
	prev = NULL;
	current = *to_pars;
	if (!environment)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(current->cmd, "$") == 0 && current->next)
			current = current->next;
		if (ft_strcmp(current->cmd, "$?") == 0 && current->next)
		{
			current->cmd = ft_itoa(error_status);
			if (!current->cmd || garbagge(ADD, current->cmd, PARS))
				return (NULL);
		}
		if (!prev || (prev && ft_strcmp(prev->cmd, "<<")))
			logic_exp_quotes(error_status, i, environment, current);
		prev = current;
		current = current->next;
	}
	return (*to_pars);
}

int	ft_found_pwd(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "pwd") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

int	minishell_brain_bis(t_cmd *to_pars, t_envp *enviroment, t_exp *export,
		int error_status)
{
	int	c_pipe;

	c_pipe = found_count_pipe(to_pars);
	if (!found_count_pipe(to_pars) && found_echo(to_pars)
		&& !found_infile_or_endfile(to_pars))
	{
		found_echo(to_pars);
		error_status = found_dollar_print_variable(to_pars, error_status,
				c_pipe);
	}
	else if (!found_token(to_pars) && !found_infile_or_endfile(to_pars))
		error_status = ft_execve(to_pars, enviroment, export, error_status);
	else
		error_status = ft_execve(to_pars, enviroment, export, error_status);
	return (error_status);
}

t_brain	*init_brain(void)
{
	t_brain	*brain;

	brain = (t_brain *)malloc(sizeof(t_brain));
	if (!brain || garbagge(ADD, brain, ENV))
		(perror(" "), exit(130));
	brain->enviroment = NULL;
	brain->export = NULL;
	brain->line = NULL;
	brain->error = 0;
	brain->to_pars = NULL;
	return (brain);
}

char	*replace_v(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			s[i] = '\v';
		i++;
	}
	return (s);
}

int	minishell_brain(t_cmd *to_pars, t_envp **enviroment, t_exp **export,
		int error_status)
{
	to_pars = expand_dollar(&to_pars, *enviroment, error_status);
	if (!found_count_pipe(to_pars) && ft_found_pwd(to_pars))
		return (ft_pwd(to_pars), error_status);
	if (!found_count_pipe(to_pars) && found_unset(to_pars))
		return (unset_delete_variable(to_pars, enviroment, export),
			error_status);
	if (!found_count_pipe(to_pars) && !found_infile_or_endfile(to_pars)
		&& to_pars && !to_pars->next && found_export(to_pars))
		return (print_export_list(*export), error_status);
	if (!found_count_pipe(to_pars) && ft_envp(to_pars) == 2)
		return (print_list_envp(*enviroment), error_status);
	if (!found_count_pipe(to_pars) && to_pars->next && found_export(to_pars))
		return (add_export_env(to_pars, enviroment, export));
	if (!found_count_pipe(to_pars) && found_exit(to_pars))
		return (ft_exit(to_pars, *enviroment, *export));
	if (!found_count_pipe(to_pars) && ft_cd(to_pars))
		return (found_cd_pwd_update(to_pars, *enviroment, *export));
	return (minishell_brain_bis(to_pars, *enviroment, *export, error_status));
}

int	main_brain(char **env, t_brain *brain)
{
	if (brain->error == 999)
		brain->error = 0;
	brain->prev_err = brain->error;
	if (!brain->to_pars && brain->line)
		brain->to_pars = add_cmd_star(brain->to_pars, brain->line);
	if (brain->to_pars)
		join_found_flag(&brain->to_pars);
	if (!brain->enviroment)
		brain->enviroment = found_and_add_env(env, brain->enviroment);
	if (!brain->export)
		brain->export = add_env_with_export(brain->enviroment);
	if (brain->export)
		export_env_sort(brain->export);
	brain->error = minishell_brain(brain->to_pars, &brain->enviroment,
			&brain->export, brain->prev_err);
	return (brain->error);
}

void	ft_update_exit_code(int *error)
{
	if (g_signal_received)
	{
		if (g_signal_received == 60)
			*error = 130;
		if (g_signal_received == 59)
			*error = 130;
		if (g_signal_received == 127)
			*error = 127;
		g_signal_received = 0;
	}
}

void	head_minishell(char **env, int temp_error, t_brain *brain)
{
	set_signal_action(1);
	brain->line = display_prompt();
	if (!brain->line)
		(garbagge(FLUSH, NULL, ALL), printf("exit\n"), exit(130));
	if (brain->error)
		temp_error = brain->error;
	brain->error = error_manager(brain->line);
	if (!brain->error || g_signal_received)
	{
		brain->error = temp_error;
		temp_error = 0;
		ft_update_exit_code(&brain->error);
		if (!ft_check_only_quote(brain->line))
		{
			ft_putstr_fd("bash: : command not found\n", 2);
			brain->error = 127;
		}
		else
			brain->error = main_brain(env, brain);
	}
	if (brain->to_pars)
		brain->to_pars = free_cmds_list(brain->to_pars);
}

int	main(int ac, char **av, char **env)
{
	int		temp_error;
	t_brain	*brain;

	((void)av, (void)ac);
	brain = init_brain();
	if (!brain)
		return (124);
	g_signal_received = 0;
	temp_error = 0;
	if (ac != 1)
		return (ft_putstr_fd("Don't need arguments\n", 2), garbagge(FLUSH, NULL,
				ALL), 1);
	ft_issatty(brain, env);
	while (1)
		head_minishell(env, temp_error, brain);
	if (brain->enviroment || brain->export)
		garbagge(FLUSH, NULL, ALL);
	return (0);
}
