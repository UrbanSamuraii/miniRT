#### NAME
NAME		= miniRT

#### PATH TO SOURCES
PATH_SRCS	+= srcs/

#### SOURCES
SRCS		+= display.c
SRCS		+= error.c
SRCS		+= free.c
SRCS		+= hooks.c
SRCS		+= main.c
SRCS		+= math.c
SRCS		+= mlx_init.c
SRCS		+= parse_ac.c
SRCS		+= parse_checks.c
SRCS		+= parse_cylinders.c
SRCS		+= parse_lights.c
SRCS		+= parse_objects.c
SRCS		+= parse_planes.c
SRCS		+= parse_spheres.c
SRCS		+= parse_utils.c
SRCS		+= ray_cylinder.c
SRCS		+= ray_lights.c
SRCS		+= ray_plane.c
SRCS		+= ray_sphere.c
SRCS		+= ray_utils.c
SRCS		+= raytracing.c
SRCS		+= vec3_utils.c

vpath %.c $(PATH_SRCS)

#### OBJS
PATH_OBJS	= objs/
OBJS		= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

#### OBJ_FLAGS
OBJ_FLAGS	+= -g # debug flag, remove before push
OBJ_FLAGS	+= -O3 # debug flag, remove before push
OBJ_FLAGS	+= -I./libft
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
COMP_FLAGS	+= -g # debug flag, remove before push
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

macos: $(MACOS)

$(MACOS): $(OBJS) $(LIBFT) $(INCLUDES)
	@$(CC) $(OBJS) $(CFLAGS) -L$ (LIBFT_PATH) -lft -Lmlx_macos -lmlx_macos -framework OpenGL -framework AppKit -o $(MACOS)
	@printf "$(YELLOW)------Compilation executed------\n\n"

$(NAME): $(OBJS) $(LIBFT) $(INCLUDES) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -o $@ -L $(LIBFT_PATH) $(COMP_FLAGS)
	@printf "$(YELLOW)------Compilation executed------\n"
	@echo "$(YELLOW)         _      _ ___  ______"
	@echo "$(YELLOW)  __ _  (_)__  (_) _ \/_  __/"
	@echo "$(YELLOW) /  ' \/ / _ \/ / , _/ / /   "
	@echo "$(YELLOW)/_/_/_/_/_//_/_/_/|_| /_/    \n"

$(LIBFT):
	@$(SMAKE) -sC $(LIBFT_PATH)
	@printf "$(CYAN)--------libft.a created----------\n\n"

# A commenter si on utilise macos
$(OBJS): $(PATH_OBJS)/%.o: %.c $(INCLUDES)
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(OBJ_FLAGS)

# A decommenter si on ulitise macos
# $(OBJS): $(PATH_OBJS)/%.o: %.c $(INCLUDES)
# 	@mkdir -p $(PATH_OBJS)
# 	@$(CC) $(CFLAGS) -Imlx_macos -I./libft -I/opt/X11/include -c $< -o $@

clean:
	@$(RM) -R $(PATH_OBJS)
	@$(SMAKE) -sC $(LIBFT_PATH) clean
	@printf "$(PURPLE)------object files deleted-------\n\n"

fclean: clean
	@$(RM) $(NAME)
	@$(SMAKE) -sC $(LIBFT_PATH) fclean
	@printf "$(GREEN)----Executable files deleted-----\n\n"

re: fclean all

ra: fclean macos

.PHONY: all clean fclean re ra
