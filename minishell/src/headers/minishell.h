/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:58:13 by npaolett          #+#    #+#             */
/*   Updated: 2024/03/06 15:22:11 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include "pipex.h"
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
# include <dirent.h>

# define EXIT_FAILURE 1
# define RESET_COLOR "\001\033[0m\002"
# define COLOR_VIOLET "\001\033[0;35m\002"
# define COLOR_RED "\001\033[1;31m\002"
# define STDIN 0
# define STDOUT 1
# define INFILE 0
# define OUTFILE 1
# define ADD 0 //ajouter un pointeur
# define FREE 1 // free 1 pointeur
# define FLUSH 2 // free 1 liste
# define QUIT 3 // free toutes le listes
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
	struct	s_file	*next;
}				t_file;

typedef struct s_lists
{
	t_list	*node;
	int		list;
}	t_lists;


typedef struct s_v
{
	char	*name;
	char	*value;
	char	*modif_variable;
} 			t_v;

typedef struct s_cmd
{
	char			*cmd;
	int				count;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_execve
{
	pid_t		pid[1024];
	char		**new_enviroment;
	char		**exp;
	int			tmp_fd[1024][2];
	t_file		***pipe_redirections;
	int			fd[2];
	int			n_pipe;
	int			current_pipe;
	int			token;
	int			error;
	t_cmd		*cmd_err;
	char		*get_g_path;
	char		**good_cmd;
}				t_execve;


// ------ commande -- //


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
}				t_l_cd;


typedef struct 	s_envp
{
	char			*path;
	char			*name;
	char			*value;
	struct s_envp 	*next;
}					t_envp;


typedef	struct s_for_re
{
	int		spaces_before;
    int		spaces_after;
    int		j_after_count;
	int		len;
}				t_for_re;


typedef struct 	s_exp
{
	char			*path;
	char			*name;
	char			*value;
	struct s_exp 	*next;
}					t_exp;

typedef struct s_brain
{
	char	*line;
	int		error;
	int		prev_err;
	t_cmd	*to_pars;
	t_envp	*enviroment;
	t_exp	*export;
}			t_brain;

typedef struct s_gb
{
	int			list;
	void		*p;
}				t_gb;


// ----------- UT --------------- //

void 				remove_q(char *s);
void				print_list(t_cmd *head);
void 				print_string_array(char **array);
void				ft_free_tab_garbage(char **tab);
t_cmd	*add_new_cmd(char **commande_split, int i);
// ----------- E	RROR --------------- //
void 				close_if_open(int fd);
void				close_all_fd_tmp(t_execve *pipex, int n);
int					garbagge(int rule, void *p, int list);

void    			set_signal_action(int sig_case);
int					ft_error_directoryx(char *str);
/* void				ft_clean_spaces(char *str); */
int					count_quote(char *str, char c, char d);
/* void				change_quote_in_star(char *str); */
// void				kill_double_quote(char *str, int i, int j, int flag);
void				kill_single_quote(char *str, int i, int j, int flag);
int					kill_useless_quote(char *str);
int					kill_double_quote(char *str, int i, int j, int flag);
// int					remove_double_quotes(char *str);
int 				check_if_only_space(char *s);

// ----------- ERRORI EXEC --------------- //
void				freeList(t_cmd *head);
void 				free_list_to_pars(t_cmd **to_pars);
int					is_directory(char *s);
int					ft_error_commande_not_to_pars(t_cmd *to_pars, t_execve *pipex);
void 				ft_error_not_found_directory(t_file *file_list, t_execve *pipex, int i);
void				ft_error_redir_file(int fd, t_execve *pipex, int i, t_cmd *to_pars);
void				free_cmd_list(t_cmd *head);
t_cmd				*free_cmds_list(t_cmd *head);
// ----------- PARS --------------//
void				ft_issatty(t_brain *brain);
int					non_interactive_mode(t_brain *brain);
t_cmd				*add_cmd_list(t_cmd *list, char **commande_split, char *line);
int					join_found_flag(t_cmd **to_pars);
char				*display_prompt(void);
// void				commande_split_toParse(char **commande_split, char *line);
// char 				***split_commands(t_cmd *to_pars);
t_cmd				*expand_dollar(t_cmd **to_pars, t_envp *environment, int error_status);
t_envp				*add_node_to_end(t_envp **list, const char *name, const char *value);// void remove_tokens(char *str, const char *token);
t_envp				*logic_init_node(t_envp *new_node, const char *name, const char *value,
								char *temp);
char				**ft_split_garbage(char const *s, char c);
// ----------- GARBAGE --------------//
void				del(void *p);
void				ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
int					cmp(void *p1, void *p2);
void				logic_garbage_clear(int list, t_list *a, t_list *b, t_list *c);
int					logic_add_back(t_list **a, t_list **b, t_list **c, t_gb *gb);
/* char **ft_split_quotes_gb(char const *s, char c); */
// ----------- PIPE // REDIRECTION --------------//
t_execve			*init_structure(t_envp *enviroment, t_cmd *to_pars, t_exp *export, int error_status);
void				parent(int *fd, int i, t_execve *pipex);
// void	built_in_child_execve(t_cmd *new_to_pars, t_execve *pipex,  int j, t_envp *enviroment);
void	child_check_path_ifnt_error(t_cmd *new_to_pars, t_envp *enviroment, t_execve *pipex);
// void				child_check_path_ifnt_error(t_cmd *new_to_pars, t_envp *enviroment, t_execve *pipex);
// void	child(t_cmd *new_to_pars, int i, t_execve *pipex, int j, t_envp *enviroment, t_cmd *cmd_err);
// void				child(t_cmd *new_to_pars, int i, t_execve *pipex, int j, t_envp *enviroment);
/* void				child(t_cmd *new_to_pars, int i, char *get_good_path, t_execve *pipex, int j); */
// int	child(t_cmd *new_to_pars, int i, char *get_good_path, t_execve *pipex, t_envp *eniviroment);
int					read_here_doc(int fd, t_file *file, t_envp *enviroment);
void				redirection(int *fd, int i, t_execve *pipex);
void				redirection_simple(int *fd, int i, t_execve *pipex);
void				redirection_simple1(int *fd, int i, t_execve *pipex);
void				ft_open_redir_here_doc(t_file *file_list, t_execve *pipex, int i);
void				ft_open_redir_in_append(t_file *file_list, t_execve *pipex, int i);
void				ft_open_redir_in(t_file *file_list, t_execve *pipex, int i);
void				ft_open_redir_out(t_file *file_list, t_execve *pipex, int i);
int     			ft_execve(t_cmd *to_pars, t_envp *enviroment, t_exp *export, int error_status);
char 				**envp_list_to_new_env(t_envp *enviroment);
int					len_liste_exp(t_exp *enviromet);
char				*ft_good_path_access(t_cmd	*to_pars, t_envp *enviroment, t_execve *pipex);
int					execute_pipeline_command(t_execve *pipex, t_cmd *new_to_pars, t_envp *enviroment);

// ----------- REDIRECTION ------- //
int					found_infile_or_endfile(t_cmd *to_pars);
char				*direction_in_out_file(t_cmd	*to_pars);

// ------------ BUILDING ----------- // 
int 				split_by_quotes_and_spaces(char *str, char *tokens[]);
int					handle_quotes(char **ptr, char quote, char *tokens[], int *i);
int					find_missing_quote(char **ptr, char quote);
void				find_and_terminate_token(char **ptr);
// ------------ cd ----------- // 
int					ft_pwd(t_cmd *to_pars);
int					ft_cd(t_cmd *to_pars);
int					ft_home_not_found(char *home);
char				*home_found(char *home);
char				*old_pwd_not_found(char *pwd, t_envp *enviroment, t_exp *export);
void				found_pwd_in_env_modif(t_envp *enviroment, char *new_pwd);
void				change_env_export_pwd(t_envp *enviroment, t_exp *export, char *new_pwd);
int					found_cd_home(t_exp *export, t_envp *enviroment, char *home, char *pwd);
void				change_env_export_old_pwd(t_envp *enviroment, t_exp *export, char *old_pwd);
void				found_old_pwd_exp_and_modif(t_exp *export, char *old_pwd);
void				found_old_pwd_env_and_modif(t_envp *enviroment, char *old_pwd);
t_exp 				*old_exp_add_back(char *old_modif);
t_envp 				*old_nev_add_back(char *old_pwd, char *name_variable);
char				*ft_strnjoin(const char *s1, const char *s2, size_t n);
// ------------ BUILDING ----------- // 
// ------------ BUILDING ----------- // 

// ------------ BUILDING ----------- // 

// ------------ BUILDING ----------- // 
int     			found_export(t_cmd *to_pars);
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
void				ft_exit_neg(t_cmd *to_pars);
void				ft_exit_ls(t_cmd *to_pars);
int					check_for_max_int(char *str);
// int					print_pwd(t_envp *envp);
int					found_echo(t_cmd *to_pars);
int					print_not_found(int print_argument, t_cmd *arg_cmd);
/* int					ft_condition_printf(int print_argument, t_cmd *arg_cmd,
						char *expanded_value );*/
int					found_echo_whit_flag(t_cmd *arg_cmd);
char				*ft_expand_value(char *arg_value, int i, t_envp *environment,
						int err);
int					logic_display_error(t_cmd *arg_cmd);
char				*add_logic_garbage(char *var_value, char *found);
t_expand			*init_structure_expand(int i, int err, char *dollar);
char				*find_variable_value(char *var_name, t_envp *enviroment, int e_st);
char				*creation_var_name(int start, int i, char *arg_value);
char				*cretion_sub_string(char *value, int len_tot, char *expanded_value);
int					valid_variable_char(char c);
int					is_special_char(char c);
int					count_dollar(char *string);
char				*logic_f_dollar_int(char *current, int error_status);
char				*expnad_join_dollar(char *expanded_value, char *dollar);
char				*expand_last_dollar(char *expanded_value, char *value);
char				*expanded_var_value(char *var_value, char *expanded_value);
void				process_expand(char **value, char **expanded_value, t_expand *expand,
						t_envp *environment);
int					ft_envp(t_cmd *to_pars);
int					found_count_pipe(t_cmd *cmd);
int					valid_variable_char(char c);
t_envp				*found_and_add_env(char **env, t_envp *enviroment);
int					found_cd_pwd_update(t_cmd *to_pars, t_envp *enviroment, t_exp *export);
/* void				add_export_env(t_cmd *to_pars, t_envp **enviroment); */
int					found_dollar_print_variable(t_cmd *to_pars, int error_status);
int					logic_found_dollar_interrogation(t_cmd *current, int error_status);
// char *logic_print_variable(const char *input, t_envp *environment) ;
void				logic_expand_variable(int i, t_envp *enviroment, t_cmd *current, int e_st);
// void							logic_print_variable(int start, int	i, t_envp *enviroment, t_cmd *arg_cmd);
char				*logic_print_variable(int i, t_envp *enviroment,t_cmd *arg_cmd, int e_st);
// void logic_print_variable(int start, int i, t_envp *enviroment, t_cmd *arg_cmd, int *stop_printing);
int					add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export);
t_exp				*add_env_with_export(t_envp *enviroment);
void    			unset_delete_variable(t_cmd *to_pars, t_envp **enviroment, t_exp **export);
char 				*ft_strcpy(char *dest, const char *src, size_t size);
int					logic_print_echo(t_cmd *arg_cmd, int print_argument, char *expanded_value);
void				print_list_envp(t_envp *head);
void				print_export_list(t_exp *export);
void 				ft_swap(t_exp *a, t_exp *b);
void				export_env_sort(t_exp *exp_env);
char				*found_variable_env(t_envp *enviroment, char *name_v);
char				*found_variable_exp(t_exp *export, char *name_v);
int					is_valid_variable_char(char c);
int					found_dollar_alone(char *s);
// ------------ ERROR SYNTAX ----------- // 
int    				check_forb_logic(int i, char c, char *str);
int					check_alone(char *s);
int					ft_only_pipe(char *str);
int					special_redir_case(char *str);
int					ft_error_pipe_in_pipe(char *str);
int					ft_error_pipe_no_word(char *str, int i, int count);
void				ft_exit(t_cmd   *to_pars, t_envp *env, t_exp *exp);
void				purify(char *str);
int					error_manager(char *str);
int					ft_error_case_1(char c);
int					ft_error_blank(char *str);
int					ft_error_shift_operator(char *str);
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
/* int 				check_only_single_space(char *s); */


#endif