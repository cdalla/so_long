NAME = so_long

CC = gcc

MLX = mlx/libmlx.a

CFLAGS = -Wall -Werror -Wextra 

SRC =	map_check.c\
		GNL/get_next_line.c\
		GNL/get_next_line_utils.c\
		utils.c\
		game.c\
		map_to_image.c\
		key_event.c\
		libft/itoa.c\


all: $(NAME)
	
$(NAME): $(MLX) $(SRC) 
	$(CC) $(CFLAGS) $(SRC) -Lmlx -lmlx -Imlx -framework OpenGL -framework Appkit -o $(NAME)

$(MLX):
	make -C mlx

clean:
	make clean -C mlx

fclean: clean
	make clean -C mlx
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, bonus