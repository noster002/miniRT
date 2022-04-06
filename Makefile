CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -D BUFFER_SIZE=1
RM				= rm -f
NAME			= miniRT
LIBFT			= libft/libft.a
MAKELIB			= make -C libft

SRC_ALL			= \
				src/main.c src/start_raytracing.c get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c src/input.c src/initialize.c \
				src/free.c src/atod.c src/initialize_utils1.c src/initialize_utils2.c \
				src/utils.c src/render.c src/math.c src/math_2.c src/raytracer.c \
				src/ray.c src/trace.c src/sphere.c src/plane.c src/cylinder.c \
				src/cylinder_utils.c src/shadow_ray.c src/color.c src/shadow_ray_utils.c
SRC_LINUX		= src/key_hook_linux.c
SRC_MAC			= src/key_hook_mac.c

OBJ_ALL			= $(SRC_ALL:c=o)
OBJ_LINUX		= $(SRC_LINUX:c=o)
OBJ_MAC			= $(SRC_MAC:c=o)

ifeq ($(shell uname -s),Linux)
	OBJ			= $(OBJ_ALL) $(OBJ_LINUX)
	COMPILE		= $(COMPILE_LINUX)
endif
ifeq ($(shell uname -s),Darwin)
	OBJ			= $(OBJ_ALL) $(OBJ_MAC)
	COMPILE		= $(COMPILE_MAC)
endif

MLX_LINUX		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MLX_MAC			= -Lmlx_macOS -lmlx -framework OpenGL -framework AppKit
COMPILE_LINUX	= $(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)
COMPILE_MAC		= $(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_MAC) -o $(NAME)

all:			$(NAME)

$(NAME):		$(OBJ)
				$(MAKELIB)
				$(COMPILE)

linux:
				./mlx_linux/configure

clean:
				$(RM) $(OBJ)
				$(MAKELIB) fclean

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re