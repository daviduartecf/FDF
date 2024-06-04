CC = cc -g
NAME = program
LIBX = minilibx-linux/libmlx.a
FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
SRCS = render_map.c handle_file.c gnl/get_next_line.c gnl/get_next_line_utils.c ft_split.c
all: ${NAME}

${LIBX}:
	make --silent -C minilibx-linux

${NAME}: ${LIBX}
	${CC} ${SRCS} ${LIBX} ${FLAGS} -o ${NAME}

clean:
	@rm ${NAME}

re: fclean all

.PHONY : all clean fclean re
