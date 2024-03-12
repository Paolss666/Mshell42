/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:58:13 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/12 03:04:05 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include "pipex.h"
# include <dirent.h>
# include <errno.h>
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_FAILURE 1
# define RESET_COLOR "\001\033[0m\002"
# define COLOR_VIOLET "\001\033[0;35m\002"
# define COLOR_RED "\001\033[1;31m\002"
# define STDIN 0
# define STDOUT 1
# define INFILE 0
# define OUTFILE 1
# define ADD 0   //ajouter un pointeur
# define FREE 1  // free 1 pointeur
# define FLUSH 2 // free 1 liste
# define QUIT 3  // free toutes le listes
# define ALL 10
# define PARS 12
# define EX 13
# define ENV 14

// extern int	g_exit_status;

// readline --> read a line from the terminal and return it , using prompt (char
// * prompt<-----
//

typedef struct s_file
{
	char			*redir;
	char			*nome_file;
	char			*here_doc;
	int				here_doc_fd;
	struct s_file	*next;
}					t_file;

typedef struct s_lists
{
	t_list			*node;
	int				list;
}					t_lists;

typedef struct s_v
{
	char			*name;
	char			*value;
	char			*modif_variable;
}				t_v;

typedef struct s_cmd
{
	char			*cmd;
	int				count;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_execve
{
	pid_t			pid[1024];
	char			**new_enviroment;
	char			**exp;
	int				tmp_fd[1024][2];
	t_file			***pipe_redirections;
	int				fd[2];
	int				n_pipe;
	int				current_pipe;
	int				token;
	int				error;
	t_cmd			*cmd_err;
	char			*get_g_path;
	char			**good_cmd;
	int				for_h;
}					t_execve;


typedef struct s_expand
{
	char			*dollar;
	int				i;
	int				err;
}					t_expand;

typedef struct s_l_cd
{
	char			*home;
	char			*old_pwd;
	char			*pwd;
}					t_l_cd;

typedef struct s_envp
{
	char			*path;
	char			*name;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_h_c
{
	int				fd_here_doc_input;
	int				fd_here_doc_output;
}					t_h_c;

typedef struct s_for_re
{
	int				spaces_before;
	int				spaces_after;
	int				j_after_count;
	int				len;
	int				i;
}					t_for_re;

typedef struct s_a_rdr
{
	char			*new_com;
	char			*token;
	char			*new_token;
	char			last_char;
}					t_a_re;

typedef struct s_exp
{
	char			*path;
	char			*name;
	char			*value;
	struct s_exp	*next;
}					t_exp;

typedef struct s_brain
{
	char			*line;
	int				error;
	int				prev_err;
	t_cmd			*to_pars;
	t_envp			*enviroment;
	t_exp			*export;
}					t_brain;

typedef struct s_gb
{
	int				list;
	void			*p;
}					t_gb;

typedef struct s_quote
{
	int				d_q;
	int				s_q;
	size_t			j;
	size_t			i;
}					t_quote;

typedef struct s_expp
{
    char            *value;
    char            *expanded_value;
    char            *dollar;
    int                len_tot;
    char            *tmp;
    t_quote            q;
}                    t_expp;


// ----------- UT --------------- //
void				cook(size_t *k, t_quote q, const char *src);
int					ft_found_pwd(t_cmd *to_pars);
void				remove_q(char *s);
void				remove_quote(char *s);
// void				print_list(t_cmd *head);
void				print_string_array(char **array);
void				ft_free_tab_garbage(char **tab);
t_cmd				*add_new_cmd(char **commande_split, int i);
// ----------- E	RROR --------------- //
void				close_if_open(int fd);
void				close_all_fd_tmp(t_execve *pipex, int n);
int					garbagge(int rule, void *p, int list);
void				set_signal_action(int sig_case);
int					count_quote(char *str, char c, char d);
void				kill_single_quote(char *str, int i, int j, int flag);
int					kill_useless_quote(char *str);
int					kill_double_quote(char *str, int i, int j, int flag);
int					check_if_only_space(char *s);
// ----------- ERRORI EXEC --------------- //
int					is_directory(char *s);
int					ft_error_commande_not_to_pars(t_cmd *to_pars,
						t_execve *pipex);
void				ft_error_not_found_directory(t_file *file_list,
						t_execve *pipex, int i);
void				ft_error_redir_file(int fd, t_execve *pipex, int i,
						t_cmd *to_pars);
void				free_cmd_list(t_cmd *head);
t_cmd				*free_cmds_list(t_cmd *head);
// ----------- PARS --------------//

int					main_brain(char **env, t_brain *brain);
void				ft_issatty(t_brain *brain, char **env);
int					non_interactive_mode(t_brain *brain, char **env);
t_cmd				*add_cmd_list(t_cmd *list, char **commande_split,
						char *line);
int					join_found_flag(t_cmd **to_pars);
char				*display_prompt(void);
t_cmd				*expand_dollar(t_cmd **to_pars, t_envp *environment,
						int error_status);
t_envp				*add_node_to_end(t_envp **list, const char *name,
						const char *value);
t_envp				*logic_init_node(t_envp *new_node, const char *name,
						const char *value, char *temp);
char				**ft_split_garbage(char const *s, char c);
void	logic_found_shlvl_env(t_envp *enviroment);
char	*found_path_envp_list(t_envp *enviroment);
int		found_pwd(t_cmd *to_pars);
void	change_in_exp(t_exp *export);
int    ft_check_only_quote(char *line);
char	*logic_get_good_path(char **with_flag, char **env_split,
		t_execve *pipex);
void	replace_quotes(char *str);
int	contains_only_spaces(const char *str);
int	has_both_quotes(const char *str);
int	count_single_quotes(char *cmd);
int	logic_check_type_quotes(char *str);
void	logic_exp_quotes(int r_st, int i, t_envp *environment, t_cmd *current);
char	*ft_strndup_g(const char *src, size_t n);
t_brain	*init_brain(void);
int	minishell_brain_bis(t_cmd *to_pars, t_envp *enviroment, t_exp *export,
		int error_status);
// ----------- GARBAGE --------------//
int					ft_check_only_quote(char *line);
void				del(void *p);
void				ft_list_remove_if(t_list **begin_list, void *data_ref,
						int (*cmp)());
int					cmp(void *p1, void *p2);
void				logic_garbage_clear(int list, t_list *a, t_list *b,
						t_list *c);
int					logic_add_back(t_list **a, t_list **b, t_list **c,
						t_gb *gb);
// ----------- PIPE // REDIRECTION --------------//
void	child(t_cmd *new_to_pars, t_execve *pipex, int i, t_envp *enviroment);
void	add_command_to_list_token(t_cmd **command_list, t_cmd *command);
void	handle_pipe_case(t_cmd *temp, t_cmd *prev_temp, t_cmd *command_list);
t_cmd	*loop_p_for_token(t_cmd *command_list, t_cmd *temp, t_cmd *prev_temp,
		t_cmd *current_command);
t_cmd	*parse_for_token(t_cmd *to_pars);
void	creation_cmd(t_cmd **current_commande, const char *new_cmd);
void	creation_cmd_empty(t_cmd **current_commande, const char *new_cmd);
int	get_file_list_array_size(t_file ***file);
char	*change_in_quotes_espace(char *cmd, char replacement);
void	found_echo_in_pipe(t_cmd *new_to_pars);
void	found_echo_in_pipe_flag(char **tmp);
void	print_env_array(char **str_array);
const char	*found_in_env_char(char **envi);
void	found_pwd_in_pipe(t_execve *pipex);
void	print_err_to_not_numb(char *exit_r);
void	found_exit_in_pipe(t_cmd *ntp);
void	found_export_in_pipe(char *cmd, t_execve *pipe);
void	found_env_in_pipe(char *cmd, t_execve *pipe);
int	found_in_to_pars(t_cmd *current);
void	pass_execve(char **good_commande, char *get_good_path, t_execve *pipex,
		int i);
void				close_if_plus_zero(t_execve *pipex);
int					ft_check_valid_flag_echo(char *s);
int					if_not_numeric(char *s);
t_execve			*init_structure(t_envp *enviroment, t_cmd *to_pars,
						t_exp *export, int error_status);
void				parent(int *fd, int i, t_execve *pipex);
void				child_check_path_ifnt_error(t_cmd *new_to_pars,
						t_envp *enviroment, t_execve *pipex, char **tmp);
int					read_here_doc(int fd, t_file *file, t_envp *enviroment);
int					ft_found_here_doc(t_file *new_node, char *here_doc,
						t_envp *enviroment);
void				redirection(int *fd, int i, t_execve *pipex);
void				redirection_simple(int *fd, int i, t_execve *pipex);
void				redirection_simple1(int *fd, int i, t_execve *pipex);
void				ft_open_redir_here_doc(t_file *file_list, t_execve *pipex,
						int i);
void				ft_open_redir_in_append(t_file *file_list, t_execve *pipex,
						int i);
void				ft_open_redir_in(t_file *file_list, t_execve *pipex, int i);
void				ft_open_redir_out(t_file *file_list, t_execve *pipex,
						int i);
int					ft_execve(t_cmd *to_pars, t_envp *enviroment, t_exp *export,
						int error_status);
char				**envp_list_to_new_env(t_envp *enviroment);
int					len_liste_exp(t_exp *enviromet);
char				*ft_good_path_access(t_cmd *to_pars, t_envp *enviroment,
						t_execve *pipex);
int					execute_pipeline_command(t_execve *pipex,
						t_cmd *new_to_pars, t_envp *enviroment);
int					echo_flag_funny(t_cmd *to_pars, t_cmd *arg_cmd,
						int error_status);
// ----------- REDIRECTION ------- //
int					found_infile_or_endfile(t_cmd *to_pars);
char				*direction_in_out_file(t_cmd *to_pars);
void	append_to_list_red(t_cmd **new_list, t_cmd *cmd);
t_cmd	*add_cmd_for_redir(t_cmd *list);
void	add_ep_redirection_and_pipes(t_cmd *head);
t_a_re	*add_init(void);
char	*new_cmd_for_token(char *token);
void	add_spaces_around_token(char *token, char **new_token, char *last_char);
char	*check_redir_for_split(char *cmd);
t_for_re	*init_esp(char *cmd);
t_cmd	*add_redirection_to_list(t_cmd **new_list_ptr, t_cmd *prev,
		t_cmd *current);
t_cmd	*remove_redirections(t_cmd *to_pars);
void	add_spaces_around_token(char *token, char **new_token, char *last_char);
char	*new_cmd_for_token(char *token);
void	count_spaces_before_and_after(char *str, int index, t_for_re *re);
t_cmd	*parsing_before_pipe_red(t_cmd *to_pars);
t_cmd	*copy_node(t_cmd *original);
char	*create_temp_buffer(const char *str1, const char *str2);
void	creation_cmd(t_cmd **current_commande, const char *new_cmd);
void	found_echo_in_pipe(t_cmd *new_to_pars);
void	found_echo_in_pipe_flag(char **tmp);
void	print_env_array(char **str_array);
const char	*found_in_env_char(char **envi);
void	found_pwd_in_pipe(t_execve *pipex);
void	print_err_to_not_numb(char *exit_r);
void	found_exit_in_pipe(t_cmd *ntp);
void	found_export_in_pipe(char *cmd, t_execve *pipe);
void	found_env_in_pipe(char *cmd, t_execve *pipe);
int	found_in_to_pars(t_cmd *current);
void	postfork_ms_sig(int signal);
void	ms_signals(void);
int	len_liste_cmd(t_cmd *cmd);
void	logic_wait_pd(t_execve *pipex, int n);
// -----------  ------- //
size_t				find_next_non_n_index(const char *cmd);
char				*ft_strcp_for_me(char *dest, const char *src);
int					found_echo_not_flag(t_cmd *arg_cmd);
int					logic_print_echo(t_cmd *arg_cmd,
						int print_argument, char *expanded_value);
int					logic_print_echo_flag(t_cmd *to_pars, int error_status);
size_t				funny_c_echo_logic(const char *cmd,
						size_t idx, size_t cmd_len);
// ------------ BUILDING ----------- //
int					process_echo_dash(t_cmd *to_pars, char *tmp);
int					found_with_check_flag(t_cmd *to_pars, char *tmp);
void				add_environment_variable(t_envp **enviroment, char *name_v, char *value);
void				found_name_v_only_in_export(t_exp *new_upgrade_exp, char *name_v,
									char *value);
void				found_name_both_env(char *value, char *name_v, char *modif_variable,
						t_envp *current);
void				found_name_both_expo(char *modif_variable,
						char *value, char *name_v, t_exp *new_upgrade_exp);
char				*found_plus_modif_path(t_exp *new_upgrade_exp, char *value,
						char *modif_variable);
char				*modif_variable_exp(char *name_v, char *value);
void				add_export_variable(t_exp **export, char *name_v, char *value);
int					check_export_variable_exists(char *check_equal, char *check_name_v,
						t_exp **check_equal_list);
t_exp				*ft_new_export(char *name_v, char *value);
t_exp				*add_list_export(char *name_v, char *found_equal, t_exp **export);
int					add_export_variable_pro(char *line, char *found_equal, t_exp **export,
						t_exp *check_equal_list);
void				add_both_list(t_exp **export, t_envp **enviroment, char *name_v,
						char *value);
t_envp				*find_in_environment_list(t_envp *enviroment, char *name_v);
t_exp				*find_in_export_list(t_exp *export, char *name_v);
void				logic_add_in_exp_env(t_envp **enviroment, t_exp **export, t_v *v,
						char *modif_variable);
t_v					*init_v(char *line, char *found_equal);
void				update_environment_and_export(t_envp **enviroment, t_exp **export,
					char *line, char *found_equal);
void				udpate_plus_after_env_exp(t_envp **enviroment, t_exp **export, char *line, char *found_equal);
int					is_valid_export_value(char *cmd);
void				remove_q(char *s);
void				ft_export_logic( t_envp **enviroment, t_exp **export, char *line);
int					check_plus_before(char *line);
int					add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export);
int	handle_export_error(char *cmd);
// int					handle_quotes(char **ptr, char quote, char *tokens[],
// 						int *i);
// int					find_missing_quote(char **ptr, char quote);
// void				find_and_terminate_token(char **ptr);
// ------------ cd ----------- //
int					ft_pwd(t_cmd *to_pars);
int					ft_cd(t_cmd *to_pars);
int					ft_home_not_found(char *home);
char				*home_found(char *home);
char				*old_pwd_not_found(char *pwd, t_envp *enviroment,
						t_exp *export);
void				found_pwd_in_env_modif(t_envp *enviroment, char *new_pwd);
void				change_env_export_pwd(t_envp *enviroment, t_exp *export,
						char *new_pwd);
int					found_cd_home(t_exp *export, t_envp *enviroment, char *home,
						char *pwd);
void				change_env_export_old_pwd(t_envp *enviroment, t_exp *export,
						char *old_pwd);
void				found_old_pwd_exp_and_modif(t_exp *export, char *old_pwd);
void				found_old_pwd_env_and_modif(t_envp *enviroment,
						char *old_pwd);
t_exp				*old_exp_add_back(char *old_modif);
t_envp				*old_nev_add_back(char *old_pwd, char *name_variable);
char				*ft_strnjoin(const char *s1, const char *s2, size_t n);
// ------------ BUILDING ----------- //
// ------------ BUILDING ----------- //
t_exp				*init_export(t_envp *enviroment);
// ------------ BUILDING ----------- //
int					found_pwd(t_cmd *to_pars);
int					found_token(t_cmd *to_pars);
t_cmd				*add_cmd_star(t_cmd *list, char *line);
int					len_liste_exp(t_exp *enviromet);
int					len_liste_envp(t_envp *enviromet);
// ------------ BUILDING ----------- //
int					found_export(t_cmd *to_pars);
int					found_unset(t_cmd *to_pars);
int					found_exit(t_cmd *to_pars);
void				logic_shlvl_exit_exp(t_exp *export);
void				logic_shlvl_exit_env(t_envp *enviroment);
void				check_shlvl_expo(t_exp *export);
void				found_shlv_exit(t_envp *enviroment, t_exp *export);
char				*ft_clean_exit(char *str);
int					has_number(char *str);
int					before_num_is_right(char *str);
int					after_num_is_right(char *str);
void				too_much_arg_neg(void);
int					ft_exit_neg(t_cmd *to_pars);
int					ft_exit_ls(t_cmd *to_pars);
int					check_for_max_int(char *str);
// int					print_pwd(t_envp *envp);
int					found_echo(t_cmd *to_pars);
int					print_not_found(int print_argument, t_cmd *arg_cmd);
/* int					ft_condition_printf(int print_argument, t_cmd *arg_cmd,
						char *expanded_value );*/
int					found_echo_whit_flag(t_cmd *arg_cmd);
char				*ft_expand_value(char *arg_value, int i,
						t_envp *environment, int err);
int					logic_display_error(t_cmd *arg_cmd);
char				*add_logic_garbage(char *var_value, char *found);
t_expand			*init_structure_expand(int i, int err, char *dollar);
char				*find_variable_value(char *var_name, t_envp *enviroment,
						int e_st);
char				*creation_var_name(int start, int i, char *arg_value);
char				*cretion_sub_string(char *value, int len_tot,
						char *expanded_value);
int					valid_variable_char(char c);
int					is_special_char(char c);
int					count_dollar(char *string);
char				*logic_f_dollar_int(char *current, int error_status);
char				*expnad_join_dollar(char *expanded_value, char *dollar);
char				*expand_last_dollar(char *expanded_value, char *value);
char				*expanded_var_value(char *var_value, char *expanded_value);
void				process_expand(char **value, char **expanded_value,
						t_expand *expand, t_envp *environment);
// char	*expnad_join_dollar(char *expanded_value, char *dollar);
void				join_not_expand(char **value, char **expanded_value);
int					ft_envp(t_cmd *to_pars);
char				*found_shlvl_init(char *env);
int					found_count_pipe(t_cmd *cmd);
int					valid_variable_char(char c);
t_envp				*found_and_add_env(char **env, t_envp *enviroment);
int					found_cd_pwd_update(t_cmd *to_pars, t_envp *enviroment,
						t_exp *export);
/* void				add_export_env(t_cmd *to_pars, t_envp **enviroment); */
int					found_dollar_print_variable(t_cmd *to_pars,
						int error_status, int c_pipe);
int					logic_found_dollar_interrogation(t_cmd *current,
						int error_status);
// char *logic_print_variable(const char *input, t_envp *environment) ;
void				logic_expand_variable(int i, t_envp *enviroment,
						t_cmd *current, int e_st);
// void							logic_print_variable(int start, int	i,
										// t_envp *enviroment, t_cmd *arg_cmd);
char				*logic_print_variable(int i, t_envp *enviroment,
						t_cmd *arg_cmd, int e_st);
// void logic_print_variable(int start, int i, t_envp *enviroment,
		// t_cmd *arg_cmd, int *stop_printing);
int					add_export_env(t_cmd *to_pars, t_envp **enviroment,
						t_exp **export);
t_exp				*add_env_with_export(t_envp *enviroment);
void				unset_delete_variable(t_cmd *to_pars, t_envp **enviroment,
						t_exp **export);
char				*ft_strcpy(char *dest, const char *src, size_t size);
int					logic_print_echo(t_cmd *arg_cmd, int print_argument,
						char *expanded_value);
void				print_list_envp(t_envp *head);
void				print_export_list(t_exp *export);
void				ft_swap(t_exp *a, t_exp *b);
void				export_env_sort(t_exp *exp_env);
char				*found_variable_env(t_envp *enviroment, char *name_v);
char				*found_variable_exp(t_exp *export, char *name_v);
int					is_valid_variable_char(char c);
int					found_dollar_alone(char *s);
int					ft_exit_neg(t_cmd *to_pars);
void	err_neg_max_int(char *cmd);
int	check_plus_arg_neg(void);
// ------------ ERROR SYNTAX ----------- //
int					check_forb_logic(int i, char c, char *str);
int					check_alone(char *s);
int					ft_only_pipe(char *str);
int					special_redir_case(char *str);
int					ft_error_pipe_in_pipe(char *str);
int					ft_error_pipe_no_word(char *str, int i, int count);
int					ft_exit(t_cmd *to_pars, t_envp *env, t_exp *exp);
void				purify(char *str);
int					error_manager(char *str);
int					ft_error_case_1(char c);
int					ft_error_blank(char *str);
int					ft_error_shift_operator(char *str, int i, int count);
int					ft_error_backslash(char *str);
void				replace_spaces(char *str);
// int					ft_error_directoryE(char *str);
int					count_redir(char *str, char c);
int					ft_redir_before_pipe(char *str);
int					contradicting_redir(char *str);
int					ft_check_multiple_operator(char *str);
int					ft_error_bracket(char *str);
int					too_many_redirection(char *str);
int					check_multipless_left(char *str);
int					ft_error_pipe(char *str);
int					ft_error_operand(char *str, char *error_message);
int					check_multiple_right(char *str);
// char				*epur_str(char *to_epur);
void				ft_handle_quote(char *str);
int					ft_count_sign(char *str, char c);
int					ft_error_parenthesis(char *str);
int					ft_error_semicol(char *str);
int					ft_error_stx(char *str);
int					is_error(char *to_epur);
// int	is_directory(char *s);
void	ft_error_commande_split(char *cmd);
void	ft_error_quotes(t_execve *pipex, char *cmd);
void	ft_error_single_quotes(t_execve *pipex, char *cmd);
int	logic_split_for_commande(char *cmd, t_execve *pipex);
/* int 				check_only_single_space(char *s); */
// int	ft_error_commande_not_to_pars(t_cmd *to_pars, t_execve *pipex);
char				**ft_split_garbage_gogo(char const *s, char c);
void				ft_strlcpy_msh(char *token, const char *src, size_t size,
						size_t *k);
size_t				ft_strl(const char *s);
int					ft_isspace(char c);
void				ft_inc_quote(char c, int *d_q, int *s_q);
int					ft_count_word(const char *s);
char				**ft_split_garbage_gogo_quote(char const *s, char c);
t_quote				ini_for_quote(void);
#endif