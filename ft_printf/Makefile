# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 09:40:29 by daduarte          #+#    #+#              #
#    Updated: 2024/04/29 09:13:04 by daduarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
INCLUDE = includes
SRC_DIR = srcs/
LIBC = ar rcs
LIBFT = libft
RM = rm -f
CC = cc

#Sources
SRC_FILES = $(addprefix $(SRC_DIR), ft_specifiers.c ft_print_hex.c ft_helpers.c ft_printf.c)

OBJS = $(SRC_FILES:.c=.o)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	${CC} ${CFLAGS} -I${INCLUDE} -c $< -o $@

${NAME}: ${OBJS}
	@make -C ${LIBFT}
	@cp libft/libft.a .
	@mv libft.a ${NAME}
	@${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	@make clean -C ${LIBFT}

fclean: clean
	@${RM} -f ${NAME}
	@${RM} -f ${OBJS}
	@${RM} -f ${LIBFT}/libft.a

re: fclean all

.PHONY : all clean fclean re
