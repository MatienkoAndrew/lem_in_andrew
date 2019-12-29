# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 17:40:37 by fgeruss           #+#    #+#              #
#    Updated: 2019/12/29 14:07:25 by fgeruss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

FLAGS = -Wall -Wextra -Werror

FUNC = main \
	   validate \
	   validate1 \
	   validate2 \
	   validate3 \
	   bfs \
	   bfs_1 \
	   delete_useless_links \
	   align_links \
	   orientir_graph \
	   delete_dead_ends \
	   delete_input_forks \
	   delete_output_forks \
	   form_paths \
	   for_norm \
	   for_norm_1 \
	   for_memory_2 other_help


HEADER = -I includes/

SRC = $(addprefix src/, $(addsuffix .c, $(FUNC)))

OBJ = $(addprefix build/, $(addsuffix .o, $(FUNC)))

#=====COLOUR========
RED = \033[1;31m
GREEN = \033[1;92m
BLUE = \033[34;1m
YELLOW = \033[0;33m
#===================

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling... Wait a sec."
	@make -C libft
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(HEADER) -L libft/ -lft
	@echo "$(YELLOW)(•̀ᴗ•́)و $(NAME) generated!"

./build/%.o: ./src/%.c
	@gcc $(FLAGS) -o $@ -c $< $(HEADER)

norm :
	@norminette $(SRC)

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJ)
	@echo "  $(GREEN)OBJ files have been deleted."

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)
	@echo "  $(GREEN)$(NAME) have been deleted."

re: fclean all

