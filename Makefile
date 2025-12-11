NAME = miniRT

CFLAGS = -Wall -Wextra -Werror

CC = cc

SRCS =  ./init/check.c \
	./math/vector.c \
	./render/raytrace.c \
	./hit/sphere.c \
	./hit/plane.c \
	./hit/cylinder.c \
	./utils/collector.c \
	./utils/ft_split.c \
	./get_next_line/get_next_line.c \
	./get_next_line/get_next_line_utils.c \
	./init/init_context.c \
	./init/init_object.c \
	./utils/print_struct.c \
	./utils/utils.c \
	./mlx_utils/init.c \
	./main.c \

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(sort $(dir $(SRCS)))

MLX_PATH = ./minilibx_linux
MLX_LIB  = $(MLX_PATH)/libmlx.a
MLX      = -L$(MLX_PATH) -lmlx -Imlx -lXext -lX11 -lm -lbsd
INCLUDES = -I/usr/include -I$(MLX_PATH)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

all: $(NAME)

$(MLX_LIB):
	make -C $(MLX_PATH)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX) -o $(NAME) 

clean: 
	rm -rf $(OBJ_DIR)
	make -C $(MLX_PATH) clean

norm :
	norminette $(SRCS) ./includes/mini_rt.h

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean