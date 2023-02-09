NAME = so_long
SRCS = src/main.c src/check.c src/imgs.c src/utils_map.c src/utils.c \
		src/memory_utils.c
LIBFT = libft/libft.a
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MLX_FLAGS = -lmlx -Lmlx -framework OpenGl -framework Appkit 
MLX = mlx/libmlx.a
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNL_OBJS = get_next_line/get_next_line.o get_next_line/get_next_line_utils.o

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL_OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL_OBJS) $(MLX_FLAGS) -o $(NAME)
$(LIBFT):
	make -C libft
$(MLX):
	make -C ./mlx
$(GNL_OBJS): $(GNL) 
	make -C ./get_next_line
%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
clean:
	${RM} ${OBJS}
fclean: clean
	${RM} ${NAME}
fclean_libft:
	make fclean -C ./libft 
clean_gnl:
	make clean -C ./get_next_line
re: fclean all

.PHONY: all clean fclean re clean_gnl fclean_libft