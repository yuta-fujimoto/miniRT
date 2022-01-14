NAME = ray
SRCS_DIR = .
SRCS_NAME = circle.c \
			vector_utils.c
SRCS = ${addprefix ${SRCS_DIR}/, ${SRCS_NAME}}
MINIRT_H = ../srcs
MLX_DIR = ../minilibx-linux
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ${MLX_DIR} -I ${MINIRT_H}
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -C ${MLX_DIR}
	${CC} ${C_FLAGS} -o ${NAME} ${OBJS} -L ${MLX_DIR} -lmlx -lXext -lX11 -lm

clean:
	$(MAKE) clean -C ${MLX_DIR}
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
