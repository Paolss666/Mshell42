# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 16:22:18 by npaolett          #+#    #+#              #
#    Updated: 2024/03/12 03:10:00 by npoalett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc

RM = rm -fr

CFLAGS = -g3 -Wall -Wextra -Werror 

INCL = -I ./libft 

SRC =	src/builtins/ft_pwd.c\
		src/builtins/env/ft_env.c \
		src/builtins/env/ft_utils_env.c \
		src/builtins/echo/ft_echo.c \
		src/builtins/echo/ft_logic_echo.c \
		src/builtins/echo/ft_logic_echo3.c \
		src/builtins/echo/ft_utils_echo.c \
		src/builtins/echo/ft_utils_echo2.c \
		src/builtins/echo/ft_utils_echo4.c \
		src/builtins/echo/ft_utils_echo5.c \
		src/builtins/echo/ft_expand_value.c \
		src/builtins/echo/ft_utils_expand_value.c \
		src/execve/ft_init_execve.c \
		src/builtins/ft_exit.c  \
		src/builtins/ft_exit_logic.c  \
		src/builtins/ft_exit_logic2.c  \
		src/builtins/ft_exit_shlvl.c  \
		src/builtins/cd/ft_cd.c 	  \
		src/builtins/cd/ft_utils_cd.c 	 \
		src/builtins/cd/ft_logic_cd.c 	 \
		src/builtins/cd/ft_logic_cd2.c 	 \
		src/builtins/export/ft_export.c  \
		src/builtins/export/ft_logic_export.c  \
		src/builtins/export/ft_utils_export.c  \
		src/builtins/export/ft_utils_export2.c  \
		src/builtins/export/ft_utils_export3.c  \
		src/builtins/export/ft_utils_export4.c  \
		src/builtins/export/ft_utils_export5.c  \
		src/builtins/ft_unset.c    \
		src/execve/ft_exceve.c	 \
		src/execve/ft_b_in.c	 \
		src/execve/ft_b_in2.c	 \
		src/execve/ft_for_signal.c	 \
		src/execve/ft_execve_et_wait.c\
		src/execve/ft_utils_execve2.c	 \
		src/execve/ft_logic_exceve.c	 \
		src/execve/ft_utils_exceve.c	 \
		src/execve/ft_redirection_in_out.c \
		src/execve/ft_redir_open_err_et_err.c \
		src/execve/ft_redir_utils.c \
		src/execve/ft_redir_utils2.c \
		src/execve/ft_redir_utils3.c \
		src/execve/ft_utils_exce.c \
		src/execve/ft_error_print.c \
		src/execve/ft_here_doc.c \
		src/execve/ft_print_err.c \
		src/execve/ft_execve_child.c \
		src/parsing/ft_non_inter.c \
		src/parsing/parsing_commandes.c \
		src/parsing/garbage_logic.c \
		src/parsing/garbage.c \
		src/parsing/ft_free_all_list.c \
		src/parsing/split_garbage.c \
		src/signal/set_signal_action.c\
		src/error_manager/error_manager.c \
		src/error_manager/error_manager_2.c \
		src/error_manager/quote.c   \
		src/error_manager/ft_clean_spaces.c   \
		src/error_manager/ft_error_pipe_2.c \
		src/error_manager/ft_error_case_1.c \
		src/error_manager/ft_error_blank.c    \
		src/error_manager/ft_error_shift_operator.c\
		src/error_manager/ft_error_shift_operator2.c\
		src/error_manager/ft_error_shift_operator3.c\
		src/error_manager/ft_error_shift_operator4.c\
		src/error_manager/ft_error_pipe.c		\
		src/error_manager/ft_error_operand.c	\
		src/error_manager/ft_count_sign.c		\
		src/error_manager/ft_error_parenthesis.c\
		src/error_manager/ft_error_backslash.c\
		src/error_manager/ft_error_semicol.c \
		src/error_manager/ft_error_stx.c   \
		src/error_manager/ft_error_bracket.c\
		src/error_manager/purify.c\
		src/parsing/split_gogo_utils.c \
		src/parsing/split_gogo.c\
		src/parsing/ft_exp_quot.c\
		src/parsing/split_gogo_quote.c \
		src/parsing/ft_quotes_main.c \
		src/parsing/ft_found_inmain.c \
		src/parsing/ft_logic_main.c \
		src/parsing/ft_quotes_main2.c \
		src/parsing/ft_utils_for_cmd.c \
		src/parsing/ft_utils_check_path.c \
		src/parsing/ft_exp_goodpth.c \
		src/parsing/main.c \

OBJ = $(SRC:.c=.o)
# OBJ_BONUS = $(SRC_BONUS:.c=.o)


LIBFT = ./libft/libft.a


$(NAME): $(OBJ)
	make lib
	cc -o $(NAME) $(OBJ) $(LIBFT) -lreadline 

# $(BONUS): $(OBJ_BONUS)
 # make lib
# cc -o $(BONUS) $(OBJ_BONUS) $(LIBFT) 

all : $(NAME)

bonus : $(BONUS)

%.o: %.c
	cc $(INCL) $(CFLAGS) -o $@ -c $<


lib:
	make -C ./libft/ all
	
clean:
	@make -C libft/ clean
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(LIBFT)  $(BONUS)

re: fclean 
	make all

rebonus: fclean
		make bonus 

.PHONY: all clean fclean  