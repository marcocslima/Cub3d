# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:58:08 by alida-si          #+#    #+#              #
#    Updated: 2023/04/23 16:47:58 by alida-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

# LIBRARY #

LIBFT = ./libraries/libft/libft.a
LIBFT_PATH = ./libraries/libft
MLX = ./libraries/minilibx/libmlx.a
MLX_PATH = ./libraries/minilibx
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11

# COMPILATION #

FLAGS = -g3 -Werror -Wextra -Wall

# DELETE #

RM = rm -rf

# DIRECTORIES #

SRC_DIR = ./src/

BONUS_DIR = ./src_bonus/

VPATH =	$(SRC_DIR)\
		$(SRC_DIR)close_game\
		$(SRC_DIR)init_game\
		$(SRC_DIR)validate\
		$(SRC_DIR)ray_casting\
		$(SRC_DIR)run_game\
		$(SRC_DIR)utils\
		$(BONUS_DIR)\
		$(BONUS_DIR)close_game\
		$(BONUS_DIR)init_game\
		$(BONUS_DIR)validate\
		$(BONUS_DIR)ray_casting\
		$(BONUS_DIR)run_game\
		$(BONUS_DIR)utils


# FILES #

SOURCES =	cub3d.c\
			check_header.c\
			check_input.c\
			create_map.c\
			init_data.c\
			get_header.c\
			utils_check_file.c\
			check_map.c\
			check_map_player.c\
			check_map_walls.c\
			free_game.c\
			check_map_emp_lines.c\
			utils.c\
			finish_game.c\
			utils_print.c\
			render.c\
			moving.c\
			moving_direction.c\
			init_textures.c\
			init_utils.c\
			init_game_assets.c\
			calc_dda.c\
			get_offsets.c\
			ray_casting.c\
			render_walls.c\
			utils_looking.c

SOURCES_BONUS =	cub3d_bonus.c\
			check_header_bonus.c\
			check_input_bonus.c\
			create_map_bonus.c\
			init_data_bonus.c\
			get_header_bonus.c\
			utils_check_file_bonus.c\
			check_map_bonus.c\
			check_map_player_bonus.c\
			check_map_walls_bonus.c\
			free_game_bonus.c\
			check_map_emp_lines_bonus.c\
			utils_bonus.c\
			finish_game_bonus.c\
			utils_print_bonus.c\
			render_bonus.c\
			moving_bonus.c\
			moving_direction_bonus.c\
			minimap_bonus.c\
			init_textures_bonus.c\
			init_utils_bonus.c\
			init_game_assets_bonus.c\
			calc_dda_bonus.c\
			get_offsets_bonus.c\
			ray_casting_bonus.c\
			render_walls_bonus.c\
			utils_looking_bonus.c


# COMPILED_SOURCES #

SRC_PATH =	./
BONUS_PATH =	./
OBJ_PATH =	obj/
#SRCS =	${addprefix ${SRC_PATH}, ${SOURCES}}
OBJS =	$(addprefix $(OBJ_PATH), $(SOURCES:.c=.o))
OBJS_BONUS =	$(addprefix $(OBJ_PATH), $(SOURCES_BONUS:.c=.o))

# *************************************************************************** #

# RULES #

all: $(NAME)

$(NAME) : $(MLX) $(LIBFT) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -L$(MLX_PATH) $(MLX_FLAGS)

${OBJ_PATH}%.o:	$(SRC_PATH)%.c
	@mkdir -p obj
	@${CC} ${FLAGS} -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(MLX) $(LIBFT) $(OBJS_BONUS)
	gcc $(FLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS) -L$(MLX_PATH) $(MLX_FLAGS)

${OBJ_PATH}%.o:	$(BONUS_PATH)%.c
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
	$(RM) $(NAME) $(NAME_BONUS)
	make fclean -C ${LIBFT_PATH}

re: fclean all

rebonus: fclean bonus

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./assets/maps/teste_map.cub

run: all
	./cub3D ./assets/maps/teste_map.cub

.PHONY: all bonus clean fclean re rebonus mlx
