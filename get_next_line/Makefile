SRCS = get_next_line.c get_next_line_utils.c
OBJS = ${SRCS:.c=.o}
CC	= gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(OBJS)
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@
clean:
	${RM} ${OBJS}
re: clean all
.PHONY: all clean re