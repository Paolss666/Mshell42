# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 16:22:18 by npaolett          #+#    #+#              #
#    Updated: 2024/03/03 10:51:02 by npoalett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc

RM = rm -fr

CFLAGS = -g3 -Wall -Wextra -Werror 

INCL = -I ./libft 

SRC =	src/builtins/ft_pwd.c\
		src/builtins/env/ft_env.c \
		src/builtins/echo/ft_echo.c \
		src/builtins/echo/ft_logic_echo.c \
		src/builtins/echo/ft_logic_echo3.c \
		src/builtins/echo/ft_utils_echo.c \
		src/builtins/echo/ft_utils_echo2.c \
		src/builtins/echo/ft_expand_value.c \
		src/builtins/ft_exit.c  \
		src/builtins/ft_exit_logic.c  \
		src/builtins/ft_exit_logic2.c  \
		src/builtins/ft_exit_shlvl.c  \
		src/builtins/cd/ft_cd.c 	  \
		src/builtins/cd/ft_utils_cd.c 	 \
		src/builtins/cd/ft_logic_cd.c 	 \
		src/builtins/cd/ft_logic_cd2.c 	 \
		src/builtins/export/ft_export.c  \
		src/builtins/ft_unset.c    \
		src/execve/ft_exceve.c	 \
		src/execve/ft_logic_exceve.c	 \
		src/execve/ft_utils_exceve.c	 \
		src/execve/ft_redirection_in_out.c \
		src/parsing/ft_non_inter.c \
		src/parsing/parsing_commandes.c \
		src/parsing/garbage_logic.c \
		src/parsing/garbage.c \
		src/parsing/split_garbage.c \
		src/parsing/ft_split_quotes_gb.c \
		src/signal/set_signal_action.c\
		src/error_manager/error_manager.c \
		src/error_manager/error_manager_2.c \
		src/error_manager/quote.c   \
		src/error_manager/ft_clean_spaces.c   \
		src/error_manager/ft_error_pipe_2.c \
		src/error_manager/ft_error_directoryx.c \
		src/error_manager/ft_error_case_1.c \
		src/error_manager/ft_error_blank.c    \
		src/error_manager/ft_error_shift_operator.c\
		src/error_manager/ft_error_pipe.c		\
		src/error_manager/ft_error_operand.c	\
		src/error_manager/ft_count_sign.c		\
		src/error_manager/ft_error_parenthesis.c\
		src/error_manager/ft_error_semicol.c \
		src/error_manager/ft_error_stx.c   \

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