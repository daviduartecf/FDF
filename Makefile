CC = cc -g
NAME = fdf
MLX = minilibx-linux/libmlx.a
FT_PRINTF = ft_printf/libftprintf.a
FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Wall -Werror -Wextra
BONUS_SRCS = bonus_srcs/render_map_bonus.c bonus_srcs/handle_file_bonus.c gnl/get_next_line.c gnl/get_next_line_utils.c \
	bonus_srcs/ft_split_bonus.c bonus_srcs/project_points_bonus.c bonus_srcs/color_helpers_bonus.c \
	bonus_srcs/draw_image_bonus.c bonus_srcs/parsing_helpers_bonus.c bonus_srcs/misc_helpers_bonus.c \
	bonus_srcs/draw_image_helpers_bonus.c bonus_srcs/parsing_helpers3_bonus.c bonus_srcs/data_init_bonus.c \
	bonus_srcs/hook_functions_bonus.c bonus_srcs/boundaries_bonus.c bonus_srcs/parsing_helpers2_bonus.c \
	bonus_srcs/instructions_bonus.c bonus_srcs/hook_helpers_bonus.c
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

all: ${NAME}

${MLX}:
	@make --silent -C minilibx-linux

${FT_PRINTF}:
	@make --silent -C ft_printf

${NAME}: ${BONUS_OBJS} ${MLX} ${FT_PRINTF}
	@echo "\033[0;32mCompiling bonus program...\033[0m"
	@${CC} ${BONUS_OBJS} ${MLX} ${FT_PRINTF} ${FLAGS} -o ${NAME}
	@echo "\033[0;32mFDF Bonus program successfully compiled.\033[0m"
	
%.o: %.c
	@${CC} -c $< -o $@ -Wall -Werror -Wextra

clean:
	@rm -f ${BONUS_OBJS}
	@make --no-print-directory -C ft_printf/ fclean

fclean:	clean
	@rm ${NAME}

re: fclean all

.PHONY : all bonus clean re
