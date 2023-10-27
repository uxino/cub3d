NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./mlx -lmlx -framework AppKit -framework OpenGL
LIBFT =libft/libft.a
SRCS 	=	main.c parser/get_map.c  parser/check_map.c parser/check_map2.c\
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

OBJS= $(SRCS:.c=.o)
MINI = ./mlx/libmlx.a
RED = '\033[0;31m'

all: ${NAME}


$(MINI):
	@make -C ./mlx

$(LIBFT):
	@make -C libft/ all

$(NAME): $(MINI) $(OBJS) $(LIBFT)
	@$(CC) ${CFLAGS} $(OBJS) $(LIBFT) $(LDFLAGS)  -o $(NAME)
	@echo "\033[1;96mStarted Program\033[1;96m"

%.o: %.c
	@${CC} -c $^ -o $@ $(CFLAGS)

clean:
	@rm -rf ${OBJS}
	@make -C libft/ clean
	@echo $(R)Removed [$(OBJS)]$(B)

fclean: clean
	@rm -rf ${NAME}
	@echo $(R)Removed [$(NAME)]$(B)
	@make clean -C mlx/
	@make -C libft/ fclean

re: fclean all
.PHONY: fclean re all clean