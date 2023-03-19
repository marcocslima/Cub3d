/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:11:12 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/19 09:48:06 by mcesar-d         ###   ########.fr       */
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
#include <X11/X.h>
#include <X11/keysym.h>
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
# define W	119
# define S	115
# define D	100
# define A	97

# define RED "\033[38;2;222;56;43m"
# define RESET "\033[0m"

#define MLX_ERROR 1

#define BLUE_SKY_PIXEL 0x87CEEB
#define FLOR_PIXEL 0xE2725B
#define BRICK_PIXEL 0x6E4132
#define BEIGE_PIXEL 0xDAC8B3
#define RED_PIXEL 0xFF0000
#define BLUE_PIXEL 0x0000FF
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 0x000000

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
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_player
{
	float	dir[2];
	float	pos[2];
	float	cam_plane[2];
}	t_player;

typedef struct s_ray
{
	float	dir_x;
	float	dir_y;
}	t_ray;

typedef struct s_dists
{
	float	delta_dist_x;
	float	delta_dist_y;
	float	dist_side_x;
	float	dist_side_y;
}	t_dists;

typedef struct s_game
{
	t_map_header	*header;
	t_map			*map;
	char			**file;
	t_player		player;
	t_ray			ray;
	t_dists			dists;
	float			ang;
}	t_game;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
	int		l_side;
	t_game	*gm;
}	t_data;

/* ---------------------------------------------------------------------*\
|							close_game									|
\* ---------------------------------------------------------------------*/

void	close_game(t_game **game);
void	free_matrix(char **ptr);
void	free_map_header(t_map_header **header);
void	free_cub3d(t_game **game);

/* ---------------------------------------------------------------------*\
|							start_game									|
\* ---------------------------------------------------------------------*/

void	get_map(char **file, t_map **map);
void	get_header(t_game **game);
void	init_data(t_game **game);
void	ray_dir(float pixel, t_data *data);
void	calc_delta_dist(t_data *data);

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

//test
void	print_whole_map(t_game *game);
void	print_map(t_game *game);

#endif
