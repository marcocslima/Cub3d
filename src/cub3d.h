/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:11:12 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/21 17:03:42 by alida-si         ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libraries/minilibx/mlx.h"

# define WIDTH 1024
# define HEIGHT 768
# define TRUE 1
# define FALSE 0
# define PI 3.14159265359
# define TILE_SIZE 512
# define KEY_ESC 65307
# define W	119
# define S	115
# define D	100
# define A	97

# define RED "\033[38;2;222;56;43m"
# define RESET "\033[0m"

# define MLX_ERROR 1

# define CELL_SIZE 1

# define VERTICAL 0
# define HORIZONTAL 1

# define BLUE_SKY_PIXEL 0x87CEEB
# define FLOR_PIXEL 0xE2725B
# define BRICK_PIXEL 0x6E4132
# define BEIGE_PIXEL 0xDAC8B3
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define BLACK_PIXEL 0x000000

typedef struct s_map_header
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_map_header;

typedef struct s_map
{
	int		init;
	int		width;
	int		height;
	char	**matrix;
}	t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		*data;
	int		wdt;
	int		hgt;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_render_tx
{
	int		txt_id;
	float	wallx;
	int		txtx;
	float	step;
	float	txtpos;
}	t_render_tx;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct s_player
{
	float	dir_x;
	float	dir_y;
	float	pos_x;
	float	pos_y;
	float	cam_plane_x;
	float	cam_plane_y;
	//float	cam_plane[2];
}	t_player;

typedef struct s_ray
{
	float	dir_x;
	float	dir_y;
}	t_ray;

typedef struct s_offset
{
	float	offset_x;
	float	offset_y;
	float	first_offset_x;
	float	first_offset_y;
}	t_offset;

typedef struct s_dda
{
	float	offset_x;
	float	offset_y;
	float	first_offset_x;
	float	first_offset_y;
	int		map_pos_x;
	int		map_pos_y;
	int		map_step_x;
	int		map_step_y;
	float	line_size_x;
	float	line_size_y;
	int		hit_side;
	float	perp_dist;
	float	wall_line_height;
	float	line_start;
	float	line_end;
}	t_dda;

typedef struct s_mlx
{
	void			*ptr;
	void			*win;
}	t_mlx;


typedef struct s_texture_img
{
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
}	t_texture_img;

typedef struct s_color
{
	int	floor;
	int	ceiling;
}	t_color;


typedef struct s_game
{
	t_map_header	*header;
	t_map			*map;
	t_mlx			*mlx;
	t_img			*img;
	t_texture_img	*texture_img;
	t_color			*background_color;
	char			**file;
	t_player		player;
	t_ray			ray;
	//t_offset		offset;
	t_dda			dda;
	float			ang;
	int				cur_img;
	int				l_side;
	t_render_tx		tx_render;
}	t_game;

/* ---------------------------------------------------------------------*\
|							close_game									|
\* ---------------------------------------------------------------------*/

void	close_game(t_game **game, int exit_code);
void	free_matrix(char **ptr);
void	free_map_header(t_map_header **header);
void	free_cub3d(t_game **game);
int		end_game(t_game **game);
void	free_game_assets(t_game **game);

/* ---------------------------------------------------------------------*\
|							start_game									|
\* ---------------------------------------------------------------------*/

void	get_map(char **file, t_map **map);
void	get_header(t_game **game);
void	init_data(t_game **game);
void	init_game_assets(t_game **game);
void	init_data_assets(t_texture_img **texture_img, t_color **background_color, t_game *game);
void	init_data_mlx(t_mlx **mlx);
void	init_data_img(t_img **img);
void	get_background_rgb(t_game *game);
void	init_player(t_game *game);
void	ray_dir(float pixel, t_game **game);
void	get_offsets(t_game **game);
void	calc_dda(t_game **game);
void	calc_perp_dist(t_game **game);
void	calc_wall(t_game **game);

/* ---------------------------------------------------------------------*\
|								utils									|
\* ---------------------------------------------------------------------*/

int		check_rgb(char *info);
int		check_path(const char *path);
void	print_error_exit(t_game **game, char *msg);
void	print_error_msg(char *msg);
int		matrix_len(char **matrix);
int		check_str_is_number(char *str);
void	run_textures(t_game **game, int pixel);
void	render_textures(t_game **game, int pixel);
int		moving(int key, t_game *game);
int		looking(float ang, t_game **game);
void	plot_map(t_game *game);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, t_color *color);

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

void	init_textures(t_game **game);

void	calc_dda(t_game **game);
void	get_offsets(t_game **game);

#endif
