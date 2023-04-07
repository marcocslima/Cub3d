# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:58:08 by alida-si          #+#    #+#              #
#    Updated: 2023/04/07 02:32:55 by mcesar-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# LIBRARY #

LIBFT = ./libraries/libft/libft.a
LIBFT_PATH = ./libraries/libft
MLX = ./libraries/minilibx-linux/libmlx.a
MLX_PATH = ./libraries/minilibx-linux
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11

# COMPILATION #

FLAGS = -g3 #-Werror -Wextra -Wall

# DELETE #

RM = rm -rf

# DIRECTORIES #

SRC_DIR = ./src/

VPATH = $(SRC_DIR)\
		$(SRC_DIR)close_game\
		$(SRC_DIR)start_game\
		$(SRC_DIR)validate\
		$(SRC_DIR)utils

# FILES #

SOURCES =	cub3d.c\
			check_header.c\
			check_input.c\
			create_map.c\
			init.c\
			get_header.c\
			test.c\
			utils_check_file.c\
			check_map.c\
			check_map_player.c\
			check_map_walls.c\
			free_game.c\
			check_map_emp_lines.c\
			utils.c\
			finish_game.c\
			utils_print.c\
			rcast.c\
			render.c


# COMPILED_SOURCES #

SRC_PATH =	./
OBJ_PATH =	obj/
SRCS =	${addprefix ${SRC_PATH}, ${SOURCES}}
OBJS =	$(addprefix $(OBJ_PATH), $(SOURCES:.c=.o))

# *************************************************************************** #

# RULES #

all: $(NAME)

#$(NAME) : $(LIBFT) $(OBJS)
#	gcc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME) : $(MLX) $(LIBFT) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -L$(MLX_PATH) $(MLX_FLAGS)

${OBJ_PATH}%.o:	$(SRC_PATH)%.c
				@mkdir -p obj
				@${CC} ${FLAGS} -c $< -o $@

$(MLX):
			make -C $(MLX_PATH)

$(LIBFT):
			make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ_PATH)
	make clean -C ${LIBFT_PATH}
	make clean -C ${MLX_PATH}

fclean: clean
	$(RM) $(NAME)
	make fclean -C ${LIBFT_PATH}

re: fclean all

val: all
	valgrind --leak-check=full ./cub3D ./assets/maps/teste.cub

run: all
	./cub3D ./assets/maps/teste_map.cub

.PHONY: all bonus clean fclean re rebonus mlx
