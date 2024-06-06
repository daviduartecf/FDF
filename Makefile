CC = cc -g
NAME = program
MLX = minilibx-linux/libmlx.a
FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
SRCS = srcs/render_map.c srcs/handle_file.c gnl/get_next_line.c gnl/get_next_line_utils.c srcs/ft_split.c srcs/project_points.c srcs/color_helpers.c srcs/draw_image.c srcs/parsing_helpers.c srcs/parsing_helpers2.c
all: ${NAME}

${LIBX}:
	make --silent -C minilibx-linux

${NAME}: ${LIBX}
	${CC} ${SRCS} ${MLX} ${FLAGS} -o ${NAME}

clean:
	@rm ${NAME}

re: fclean all

.PHONY : all clean fclean re
