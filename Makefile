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
		srcs/color_utils1.c \
		srcs/color_utils2.c \
		srcs/object_color.c \
		srcs/print_debug.c \
		srcs/print_error.c \
		srcs/hook_funcs.c \
		srcs/data_set_utils.c \
		srcs/intersection_test.c \
		srcs/intersection_test_utils.c \
		srcs/raytrace.c \
		srcs/init.c \
		srcs/toon.c \
		srcs/material.c
B_SRCS := srcs/data_set_bonus.c
M_SRCS := srcs/data_set.c
OBJS := $(SRCS:.c=.o)
B_OBJS := $(B_SRCS:.c=.o)
M_OBJS := $(M_SRCS:.c=.o)
ifdef WITH_BONUS
OBJS += $(B_OBJS)
else
OBJS += $(M_OBJS)
endif

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

bonus:
	make WITH_BONUS=1

debug: $(OBJS) $(INCLUDE)
	$(MAKE) -C $(MLXDIR)
	$(MAKE) -C $(LIBDIR)
	$(MAKE) gnl
	$(CC) -o $(NAME) -g3 -fsanitize=address $(CFLAG) -I$(MLXDIR) -I/usr/include $(OBJS) $(MLXDIR)/$(MLXNAME) $(GNLFILE) $(LIBDIR)/$(LIBNAME) -lXext -lX11 -lm -pthread

clean:
	$(RM) $(OBJS) $(M_OBJS) $(B_OBJS)
	$(MAKE) clean -C $(MLXDIR)
	$(MAKE) clean -C $(LIBDIR)

fclean: clean
	$(RM) $(MLXDIR)/$(MLXNAME)
	$(RM) $(LIBDIR)/$(LIBNAME)
	$(RM) $(NAME)
	$(RM) $(GNLFILE)

re: fclean all
