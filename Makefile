CC = cc -g
NAME = fdf
BONUS = fdf_bonus
MLX = minilibx-linux/libmlx.a
FT_PRINTF = ft_printf/libftprintf.a
FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Wall -Werror -Wextra
SRCS = srcs/render_map.c srcs/handle_file.c gnl/get_next_line.c gnl/get_next_line_utils.c srcs/ft_split_fdf.c \
	srcs/project_points.c srcs/color_helpers.c srcs/draw_image.c srcs/parsing_helpers.c srcs/misc_helpers.c \
	srcs/draw_image_helpers.c srcs/parsing_helpers3.c srcs/data_init.c srcs/hook_functions.c srcs/boundaries.c \
	srcs/parsing_helpers2.c
BONUS_SRCS = bonus_srcs/render_map_bonus.c bonus_srcs/handle_file_bonus.c gnl/get_next_line.c gnl/get_next_line_utils.c \
	bonus_srcs/ft_split_bonus.c bonus_srcs/project_points_bonus.c bonus_srcs/color_helpers_bonus.c \
	bonus_srcs/draw_image_bonus.c bonus_srcs/parsing_helpers_bonus.c bonus_srcs/misc_helpers_bonus.c \
	bonus_srcs/draw_image_helpers_bonus.c bonus_srcs/parsing_helpers3_bonus.c bonus_srcs/data_init_bonus.c \
	bonus_srcs/hook_functions_bonus.c bonus_srcs/boundaries_bonus.c bonus_srcs/parsing_helpers2_bonus.c \
	bonus_srcs/instructions_bonus.c bonus_srcs/hook_helpers_bonus.c
OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

all: ${NAME}

bonus: ${BONUS}

${MLX}:
	make --silent -C minilibx-linux

${FT_PRINTF}:
	make --silent -C ft_printf

${NAME}: ${OBJS} ${MLX} ${FT_PRINTF}
	@echo "\033[0;32mCompiling program...\033[0m"
	@${CC} ${OBJS} ${MLX} ${FT_PRINTF} ${FLAGS} -o ${NAME}
	@echo "\033[0;32mFDF successfully compiled.\033[0m"

${BONUS}: ${BONUS_OBJS} ${MLX} ${FT_PRINTF}
	@echo "\033[0;32mCompiling bonus program...\033[0m"
	@${CC} ${BONUS_OBJS} ${MLX} ${FT_PRINTF} ${FLAGS} -o ${BONUS}
	@echo "\033[0;32mFDF Bonus program successfully compiled.\033[0m"
	
%.o: %.c
	@${CC} -c $< -o $@ -Wall -Werror -Wextra

clean:
	@rm -f ${OBJS}

fclean:	clean
	@rm ${NAME}

clean_bonus:
	@rm -f ${BONUS_OBJS}
	
fclean_bonus: clean_bonus
	@rm ${BONUS}

re: fclean all

rebonus: fclean_bonus bonus

.PHONY : all bonus clean clean_bonus re rebonus
