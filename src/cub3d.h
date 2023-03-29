/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:11:12 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/29 14:26:36 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <math.h>
# include "../libraries/libft/libft.h"
# include "../libraries/minilibx-linux/mlx.h"

# define WIDTH 1024
# define HEIGHT 768
# define TRUE 1
# define FALSE 0
# define PI 3.14159265359
# define TILE_SIZE 512
# define UP 1
# define DOWN 0
# define RIGHT 2
# define LEFT 3

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define W 119
# define S 115
# define D 100
# define A 97
# define ESC 65307

# define RED "\033[38;2;222;56;43m"
# define RESET "\033[0m"

# define COLOR_RED 0xFF0000
# define COLOR_BLACK 0x000000
# define COLOR_YELLOW 0xFFFF00
# define COLOR_WHITE 0xFFFFFF
# define COLOR_GRAY 0x4F4F4F

typedef struct s_map_header
{
	char	**no;
	char	**so;
	char	**we;
	char	**ea;
	char	**f;
	char	**c;
}	t_map_header;

typedef struct s_map
{
	int		init_map;
	int		map_width;
	int		map_higth;
	char	**map;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	float	x_position;
	float	y_position;
	float	delta_x;
	float	delta_y;
	float	angle;

}	t_player;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
}	t_data;

typedef struct s_game
{
	t_data			*mlx_data;
	t_img			*img_data;
	t_map_header	*header;
	t_map			*map;
	t_player		*player;
	char			**file;
}	t_game;

/* ---------------------------------------------------------------------*\
|							close_game									|
\* ---------------------------------------------------------------------*/

void	close_game(t_game **game, int exit_code);
int		close_window(t_game *game);
void	free_matrix(char **ptr);
void	free_map_header(t_map_header **header);
void	free_cub3d(t_game **game);

/* ---------------------------------------------------------------------*\
|							ray_casting									|
\* ---------------------------------------------------------------------*/

void	ray_casting(t_game *game);
int		find_wall_distance(t_game *game);
int		hit_wall(t_game *game, int y_coordinate, int x_coordinate,
			int y_step, int x_step);
int		shorter_distance(int x, int y);
int		distance_to_horizontal_wall_up(t_game *game);
int		distance_to_horizontal_wall_down(t_game *game);
int		distance_to_vertical_wall_right(t_game *game);
int		distance_to_vertical_wall_left(t_game *game);
int		looking_up(float angle);
int		looking_right(float angle);

/* ---------------------------------------------------------------------*\
|							start_game									|
\* ---------------------------------------------------------------------*/

void	get_map(char **file, t_map **map);
void	get_header(t_game **game);
void	init_data(t_game **game);

/* ---------------------------------------------------------------------*\
|								utils									|
\* ---------------------------------------------------------------------*/

int		check_rgb(char *info);
int		check_path(const char *path);
void	print_error_exit(t_game **game, char *msg);
void	print_error_msg(char *msg);
int		matrix_len(char **matrix);
int		check_str_is_number(char *str);

/* ---------------------------------------------------------------------*\
|							validate									|
\* ---------------------------------------------------------------------*/

void	check_header(t_game **game);
int		check_input(int argc, char **argv);
void	verify_empty_lines(char *file, t_game **game);
void	verify_onlyspace_line(t_game **game);
void	verify_player(t_game **game);
void	verify_top_and_bottom(t_game **game, char character);
int		verify_position(t_map *map, int j, int i);
void	verify_middle(t_game **game, char character);
void	verify_sides(t_game **game, char character);
void	verify_walls(t_game **game);
void	verify_map(t_game **game);

int		render_rect(t_game *game, int color, int rect_height, int rect_width,
			int y_position, int x_position);
int		render(t_game *game);

//test
void	print_whole_map(t_game *game);

#endif
