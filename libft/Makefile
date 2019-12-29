# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 16:09:18 by fgeruss           #+#    #+#              #
#    Updated: 2019/08/30 19:00:14 by fgeruss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_memset.c ft_putnbr.c ft_putchar.c ft_strdel.c ft_strjoin.c ft_strnew.c \
	  ft_strstr.c ft_strdup.c ft_strlen.c ft_strchr.c ft_putstr.c ft_strcmp.c ft_isdigit.c \
	  get_next_line.c ft_printf.c attribute.c printing.c print_s.c print_c.c print_d.c \
	  initialize.c digits_nbr.c print_o.c print_x.c print_u.c print_f1.c print_e.c \
	  print_e_help.c print_e_other.c print_e_other_1.c print_e_other_2.c print_e_presicion.c \
      for_norm.c ft_bzero.c ft_itoa.c ft_strnew_float.c ft_strsub.c ft_isalnum.c ft_isalpha.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@echo "Library is compiling..."
	@gcc -c $(SRC) -Wall -Wextra -Werror -I libft.h
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Library has compiled!)"

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
