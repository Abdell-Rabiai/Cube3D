# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 15:25:41 by ahmaymou          #+#    #+#              #
#    Updated: 2023/08/03 17:40:14 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d

Color_Off=\033[0m
LIGHTRED=\033[1;31m
LightBlue=\033[1;34m
LightPurple=\033[1;35m
Cyan=\033[0;36m
GREEN = \033[92m

BANNER=\
'											  '\
' ██████╗ ██╗   ██╗ ██████╗  ██████╗  ██████╗ '\
'██╔════╝ ██║   ██║ ██╔══██╗ ╚════██╗ ██╔══██╗'\
'██║      ██║   ██║ ██████╔╝  █████╔╝ ██║  ██║'\
'██║      ██║   ██║ ██╔══██╗  ╚═══██╗ ██║  ██║'\
'╚██████╗ ╚██████╔╝ ██████╔╝ ██████╔╝ ██████╔╝'\
' ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝ '
                                         
                                                                                                     
																									 
parsing_files = $(addprefix parsing_files/, check_file_errors.c checking_closed_map.c checking_map.c\
		checking_text.c init.c printing.c reading_map_text.c )
		
raycasting = $(addprefix raycasting/, mlx_files.c Fov.c raycasting.c) 

prepare_the_map = $(addprefix prepare_the_map/, init_map.c minimap.c player_and_line.c hooks.c)

get_next_line = $(addprefix get_next_line/,get_next_line.c get_next_line_utils.c)

# lexer = $(addprefix a_lexer/,fill_check_1st_list.c get_words.c syntax_checker.c syntax_checker2.c syntax_checker3.c)

# execution = $(addprefix execution/,child_processes_helpers.c execute_helpers.c initialize_data.c\
# 		execute_helpers1.c execute.c heredoc_helpers.c heredoc.c multiple_cmds.c multiple_cmds_helpers.c handle_signals.c)

# ebuiltin_functions = $(addprefix ebuiltin_functions/,echo.c env.c cd.c export.c export_helpers.c export_helpers1.c\
# 	cd_helpers1.c unset.c basic_builtins.c env_helpers.c)

# SRCS_OBJ = $(execution) $(ebuiltin_functions) $(parser) $(lexer)

INC_EXC = -I /usr/local/include
FRAMEWORK = -L /usr/local/lib/ -lmlx -framework OpenGl -framework AppKit

SRCS_OBJ = $(parsing_files) $(get_next_line) $(raycasting) $(prepare_the_map)

SRC = main.c

FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address

HEADER = cub3d.h

CC = cc

LIBS = libft/libft.a

OS = $(shell uname)

OBJ = $(SRCS_OBJ:.c=.o)

all : banner2 libftmake $(NAME)

banner2:
	@clear
	@echo "\n"
	@echo "$(LightPurple)"
	@for s in $(BANNER) ; do \
		printf "%s\n" "$$s" ; \
		sleep 0.03 ; \
	done ; \
	echo "$(LIGHTRED)                     Copyright : Black-Hole1004, Abdell-rabiai :) \n$(Color_Off)"

%.o: %.c $(HEADER)
	@printf "$(GREEN) Generating game objects... %-33.33s\r" $@
	@$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

$(NAME) : $(OBJ) $(SRC) $(HEADER)
	@$(CC) $(INC_EXC) $(FLAGS) $(SRC) $(OBJ) $(LIBS) -lreadline $(READLINE_LIB) -Imlx $(FRAMEWORK) -o $(NAME)
	@echo "\n\n\t$(Cyan) Enjoooy :)\n $(Color_Off)"

libftmake :
	@make bonus -C libft/

clean :
	@make clean -C libft
	@rm -rf $(OBJ)

fclean : clean
	@make fclean -C libft
	@rm -rf $(LIBS) $(NAME)
	@rm -rf *.dSYM .vscode

re : fclean all

.PHONY : all clean fclean re
