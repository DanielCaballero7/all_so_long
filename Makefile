NAME = so_long
SRCS = src/main.c ../get_next_line/get_next_line/get_next_line.c \
		../get_next_line/get_next_line/get_next_line_utils.c
LIBFT = ../libft/libft/libft.a
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
MLX_LINUX = -lmlx -L../mlx_linux -lXext -lX11

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MLX_LINUX) -o $(NAME)
$(LIBFT):
	make re -C ../libft/libft/
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	${RM} ${OBJS}
fclean: clean
	${RM} ${NAME}
re: fclean all

.PHONY: all clean fclean re