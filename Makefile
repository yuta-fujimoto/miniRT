NAME := miniRT
CC 	 := gcc
CFLAG := -Wall -Werror -Wextra
INCLUDE :=	srcs/miniRT.h \
			srcs/keysymdef.h
SRCS :=	srcs/main.c \
		srcs/parser_env_elems.c \
		srcs/parser_obj_elems.c \
		srcs/parser.c \
		srcs/utils1.c \
		srcs/utils2.c \
		srcs/vector_utils1.c \
		srcs/vector_utils2.c \
		srcs/vector_utils3.c \
		srcs/color_utils.c \
		srcs/color_utils2.c \
		srcs/color.c \
		srcs/print_debug.c \
		srcs/print_error.c \
		srcs/hook_funcs.c \
		srcs/intersection_test.c \
		srcs/intersection_test_utils.c \
		srcs/raytrace.c \
		srcs/init.c \
		srcs/toon.c
OBJS := $(SRCS:.c=.o)

MLXDIR := ./minilibx-linux
MLXNAME := libmlx_Linux.a

LIBDIR := ./libft
LIBNAME := libft.a

GNL := ./gnl
GNLNAME := get_next_line.o get_next_line_utils.o
GNLFILE :=  $(GNL)/get_next_line_utils.o \
			$(GNL)/get_next_line.o

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAG)  -I$(MLXDIR) -lm -c $< -o $@

all :$(NAME)

gnl: $(GNLFILE)

$(NAME): $(OBJS) $(INCLUDE)
	$(MAKE) -C $(MLXDIR)
	$(MAKE) -C $(LIBDIR)
	$(MAKE) gnl
	$(CC) -o $(NAME) $(CFLAG) -I$(MLXDIR) -I/usr/include $(OBJS) $(MLXDIR)/$(MLXNAME) $(GNLFILE) $(LIBDIR)/$(LIBNAME) -lXext -lX11 -lm -pthread

debug: $(OBJS) $(INCLUDE)
	$(MAKE) -C $(MLXDIR)
	$(MAKE) -C $(LIBDIR)
	$(MAKE) gnl
	$(CC) -o $(NAME) -g3 -fsanitize=thread $(CFLAG) -I$(MLXDIR) -I/usr/include $(OBJS) $(MLXDIR)/$(MLXNAME) $(GNLFILE) $(LIBDIR)/$(LIBNAME) -lXext -lX11 -lm -pthread

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(MLXDIR)
	$(MAKE) clean -C $(LIBDIR)

fclean: clean
	$(RM) $(MLXDIR)/$(MLXNAME)
	$(RM) $(LIBDIR)/$(LIBNAME)
	$(RM) $(NAME)
	$(RM) $(GNLFILE)

re: fclean all
