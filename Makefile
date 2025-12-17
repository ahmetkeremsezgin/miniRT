NAME        = miniRT

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O3

SRCS        = ./init/check.c \
              ./math/vector.c \
              ./render/trace.c \
              ./render/render_utils.c \
              ./render/lighting.c \
              ./render/check_obj.c \
              ./render/hit_obj.c \
              ./utils/ft_atof.c \
              ./hit/sphere.c \
              ./hit/plane.c \
              ./hit/cylinder.c \
              ./utils/collector.c \
              ./utils/ft_split.c \
              ./get_next_line/get_next_line.c \
              ./get_next_line/get_next_line_utils.c \
              ./init/init_context.c \
              ./init/init_object.c \
              ./utils/utils.c \
              ./mlx_utils/init.c \
              ./init/cam.c \
              ./math/utils.c \
              ./main.c

OBJS        = $(SRCS:.c=.o)

MLX_PATH    = ./minilibx_linux
MLX_LIB     = $(MLX_PATH)/libmlx.a
MLX_FLAGS   = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lbsd
INCLUDES    = -I/usr/include -I$(MLX_PATH)

all: $(MLX_LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_PATH)

clean:
	rm -f $(OBJS)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re