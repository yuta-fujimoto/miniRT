NAME := a.out
CC 	 := gcc
CFLAG := -Wall -Werror -Wextra
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
		srcs/color.c \
		srcs/print_debug.c \
		srcs/hook_funcs.c \
		srcs/intersection_test.c \
		srcs/intersection_test_utils.c \
		srcs/raytrace.c
OBJS := $(SRCS:.c=.o)

MLXDIR := ./minilibx-linux
MLXNAME := libmlx_Linux.a

LIBDIR := ./libft
LIBNAME := libft.a

GNL := ./gnl
GNLNAME := get_next_line_bonus.o get_next_line_utils_bonus.o
GNLFILE :=  $(GNL)/get_next_line_utils_bonus.o \
			$(GNL)/get_next_line_bonus.o

%.o: %.c
	$(CC) $(CFLAG)  -I$(MLXDIR) -lm -c $< -o $@

all :$(NAME)

gnl: $(GNLFILE)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLXDIR)
	$(MAKE) -C $(LIBDIR)
	$(MAKE) gnl
	$(CC) -o $(NAME) $(CFLAG) -I$(MLXDIR) -I/usr/include $(OBJS) $(MLXDIR)/$(MLXNAME) $(GNLFILE) $(LIBDIR)/$(LIBNAME) -lXext -lX11 -lm

debug: $(OBJS)
	$(MAKE) -C $(MLXDIR)
	$(MAKE) -C $(LIBDIR)
	$(MAKE) gnl
	$(CC) -o $(NAME) -g3 -fsanitize=address $(CFLAG) -I$(MLXDIR) -I/usr/include $(OBJS) $(MLXDIR)/$(MLXNAME) $(GNLFILE) $(LIBDIR)/$(LIBNAME) -lXext -lX11 -lm

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(MLXDIR)
	$(MAKE) clean -C $(LIBDIR)

fclean: clean
	rm -f $(MLXDIR)/$(MLXNAME)
	rm -f $(LIBDIR)/$(LIBNAME)
	rm -f $(NAME)
	rm -f $(GNL)/$(GNLNAME)

re: fclean all
