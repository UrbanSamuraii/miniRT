#### NAME
NAME		= miniRT

#### PATH TO SOURCES
PATH_SRCS	+= srcs/

#### SOURCES
SRCS		+= display.c
SRCS		+= free.c
SRCS		+= hooks.c
SRCS		+= main.c
SRCS		+= maths_utils.c
SRCS		+= mlx_init.c
SRCS		+= parse_ac.c
SRCS		+= parse_checks.c
SRCS		+= parse_cones.c
SRCS		+= parse_cylinders.c
SRCS		+= parse_init.c
SRCS		+= parse_lights.c
SRCS		+= parse_objects.c
SRCS		+= parse_planes.c
SRCS		+= parse_spheres.c
SRCS		+= parse_utils.c
SRCS		+= ray_cones.c
SRCS		+= ray_cylinders.c
SRCS		+= ray_lights.c
SRCS		+= ray_planes.c
SRCS		+= ray_spheres.c
SRCS		+= ray_utils.c
SRCS		+= raytracing.c
SRCS		+= vec3_utils.c

vpath %.c $(PATH_SRCS)

#### OBJS
PATH_OBJS	= objs/
OBJS		= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

#### OBJ_FLAGS
OBJ_FLAGS	+= -I./libft/includes
OBJ_FLAGS	+= -Imlx_linux
OBJ_FLAGS	+= -I./includes
OBJ_FLAGS	+= -I/usr/include

#### INCLUDES
INCLUDES	+= includes/proto.h
INCLUDES	+= includes/colors.h
INCLUDES	+= includes/params.h

#### COMPILATION
CC			= cc
CFLAGS		+= -Wall -Wextra -Werror 
CFLAGS		+= -mavx
SMAKE		= make --no-print-directory

#### COMP_FLAGS
COMP_FLAGS	+= -Imlx_linux
COMP_FLAGS	+= -Lmlx_linux
COMP_FLAGS	+= -L/usr/lib
COMP_FLAGS	+= -lmlx_Linux
COMP_FLAGS	+= -lXext
COMP_FLAGS	+= -lX11
COMP_FLAGS	+= -lft
COMP_FLAGS	+= -lm

#### LIBRARY
LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)/libft.a

#### MACOS
MACOS = miniRT_macos

#### COLORS
GREEN		= \033[1;92m
YELLOW		= \033[1;93m
PURPLE		= \033[1;95m
CYAN		= \033[1;96m

#### RULES
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(INCLUDES) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -o $@ -L $(LIBFT_PATH) $(COMP_FLAGS)
	@echo "$(YELLOW)------Compilation executed------"
	@echo "$(YELLOW)         _      _ ___  ______"
	@echo "$(YELLOW)  __ _  (_)__  (_) _ \/_  __/"
	@echo "$(YELLOW) /  ' \/ / _ \/ / , _/ / /   "
	@echo "$(YELLOW)/_/_/_/_/_//_/_/_/|_| /_/    \n"

$(LIBFT):
	@$(SMAKE) -sC $(LIBFT_PATH)
	@echo "$(CYAN)--------libft.a created----------\n"

$(OBJS): $(PATH_OBJS)/%.o: %.c $(INCLUDES)
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(OBJ_FLAGS)

clean:
	@$(RM) -R $(PATH_OBJS)
	@$(SMAKE) -sC $(LIBFT_PATH) clean
	@echo "$(PURPLE)------object files deleted-------\n"

fclean: clean
	@$(RM) $(NAME)
	@$(SMAKE) -sC $(LIBFT_PATH) fclean
	@echo "$(GREEN)----Executable files deleted-----\n"

re: fclean all

.PHONY: all clean fclean re
