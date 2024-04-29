BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		=	srcs/events.c \
				srcs/double_atoi.c \
				srcs/julia_set.c	\
				srcs/mandelbrot.c \
				srcs/main.c
SRCS_B		= 	srcs_bonus/main_bonus.c \
				srcs_bonus/mandelbrot_bonus.c \
				srcs_bonus/keyboard_hooks_bonus.c \
				srcs_bonus/julia_set_bonus.c \
				srcs_bonus/events_bonus.c \
				srcs_bonus/double_atoi.c	\
				srcs_bonus/burningship.c

NAME		= fractol
NAME_B		= fractol_bonus
minilibx	= mlx/libmlx.a
OBJS_DIR	= objs/
OBJS_DIR_B	= objs_b/
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_PREFIXED_B = $(addprefix $(OBJS_DIR_B), $(OBJS_B))
CC			= gcc
CC_FLAGS	= -g -Wall -Werror -Wextra
MLB_FLAGS	= -I -g3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz -lm

$(OBJS_DIR)%.o : %.c includes/fractol.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR_B)%.o : %.c includes/fractol.h
	@mkdir -p $(OBJS_DIR_B)
	@mkdir -p $(OBJS_DIR_B)srcs_bonus
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) $(CC_FLAGS) -o $(NAME) $(OBJECTS_PREFIXED) $(MLB_FLAGS)

$(NAME_B): $(OBJECTS_PREFIXED_B) maker
	@$(CC) -o $(NAME_B) $(OBJECTS_PREFIXED_B) $(CC_FLAGS) $(MLB_FLAGS)

all: $(NAME)

bonus:	$(NAME_B)

maker:
	@make -C mlx

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_B)
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make clean -C mlx
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re