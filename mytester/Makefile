CC = cc
NAME = testerout
FLAGS = -lrt -lm
SRCS = tester.c ../handle_file.c ../gnl/get_next_line.c ../gnl/get_next_line_utils.c ../ft_split.c
all: ${NAME}

${NAME}: ${LIBX}
	${CC} ${SRCS} ${FLAGS} -o ${NAME}

clean:
	@rm ${NAME}

re: fclean all

.PHONY : all clean fclean re
