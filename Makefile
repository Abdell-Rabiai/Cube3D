# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 15:25:41 by ahmaymou          #+#    #+#              #
#    Updated: 2023/08/31 13:25:07 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
BONUS_NAME = cub3d_bonus

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
                                         
# bonus                                                                                                     																 
parsing_files_b = $(addprefix bonus/parsing_files/, check_file_errors.c checking_closed_map.c checking_map.c\
		checking_text.c init.c printing.c reading_map_text.c parsing.c reading_map_text1.c)
		
raycasting_b = $(addprefix bonus/raycasting/, mlx_files.c Fov.c field_of_view.c raycasting.c raycasting1.c directions.c)

prepare_the_map_b = $(addprefix bonus/prepare_the_map/, init_map.c init_map1.c minimap.c player_and_line.c hooks.c hooks1.c)

get_next_line_b = $(addprefix bonus/get_next_line/,get_next_line.c get_next_line_utils.c)

# mandatory
parsing_files = $(addprefix mandatory/parsing_files/, check_file_errors.c checking_closed_map.c checking_map.c\
		checking_text.c init.c printing.c reading_map_text.c parsing.c reading_map_text1.c)
		
raycasting = $(addprefix mandatory/raycasting/, mlx_files.c Fov.c field_of_view.c raycasting.c raycasting1.c directions.c)

prepare_the_map = $(addprefix mandatory/prepare_the_map/, init_map.c init_map1.c minimap.c player_and_line.c hooks.c hooks1.c)

get_next_line = $(addprefix mandatory/get_next_line/,get_next_line.c get_next_line_utils.c)

INC_EXC = -I /usr/local/include
FRAMEWORK = -L /usr/local/lib/ -lmlx -framework OpenGl -framework AppKit

SRCS_OBJ = $(parsing_files) $(get_next_line) $(raycasting) $(prepare_the_map)
SRCS_OBJ_B = $(parsing_files_b) $(get_next_line_b) $(raycasting_b) $(prepare_the_map_b)

SRC = mandatory/main.c
SRC_B = bonus/main.c

FLAGS = -Ofast -Wall -Werror -Wextra

HEADER = mandatory/cub3d.h
HEADER_B = bonus/cub3d.h

CC = cc

LIBS = mandatory/libft/libft.a

OS = $(shell uname)

OBJ = $(SRCS_OBJ:.c=.o)
OBJ_B = $(SRCS_OBJ_B:.c=.o)

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
	@$(CC) $(INC_EXC) $(FLAGS) $(SRC) $(OBJ) $(LIBS) -Imlx $(FRAMEWORK) -o $(NAME)
	@echo "\n\n\t$(Cyan) Enjoooy :)\n $(Color_Off)"
	
$(BONUS_NAME) : $(OBJ_B) $(SRC_B) $(HEADER_B)
	@$(CC) $(INC_EXC) $(FLAGS) $(SRC_B) $(OBJ_B) $(LIBS) -Imlx $(FRAMEWORK) -o $(BONUS_NAME)
	@echo "\n\n\t$(Cyan) Enjoooy bonus :)\n $(Color_Off)"

libftmake :
	@make bonus -C mandatory/libft/
	
bonus : banner2 libftmake $(BONUS_NAME)

clean :
	@make clean -C mandatory/libft
	@rm -rf $(OBJ) $(OBJ_B)

fclean : clean
	@make fclean -C mandatory/libft
	@rm -rf $(LIBS) $(BONUS_NAME) $(NAME)
	@rm -rf *.dSYM .vscode .DS_Store

re : fclean all

.PHONY : all clean fclean re
