/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:24:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/22 14:45:15 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data_assets(t_texture_img **texture_img,
						t_color **background_color, t_game *game)
{
	*texture_img = (t_texture_img *) malloc(sizeof(t_texture_img));
	*background_color = (t_color *) malloc(sizeof(t_color));
	init_data_img(&(*texture_img)->ea);
	init_data_img(&(*texture_img)->no);
	init_data_img(&(*texture_img)->so);
	init_data_img(&(*texture_img)->we);
	get_background_rgb(game);
}

void	init_data_mlx(t_mlx **mlx)
{
	*mlx = (t_mlx *) malloc(sizeof(t_mlx));
	(*mlx)->ptr = mlx_init();
	(*mlx)->win = mlx_new_window((*mlx)->ptr, WIDTH, HEIGHT, "Cub3D");
}

void	init_data_img(t_img **img)
{
	*img = (t_img *) malloc(sizeof(t_img));
	(*img)->img_ptr = NULL;
	(*img)->addr = NULL;
	(*img)->data = 0;
	(*img)->bpp = 0;
	(*img)->endian = 0;
	(*img)->line_len = 0;
}

void	init_data_header(t_map_header **header)
{
	*header = (t_map_header *) malloc(sizeof(t_map_header));
	(*header)->c = NULL;
	(*header)->ea = NULL;
	(*header)->f = NULL;
	(*header)->no = NULL;
	(*header)->so = NULL;
	(*header)->we = NULL;
}

void	init_data_map(t_map **map)
{
	*map = (t_map *) malloc(sizeof(t_map));
	(*map)->height = 0;
	(*map)->width = 0;
	(*map)->init = 0;
	(*map)->matrix = NULL;
}

void	init_data(t_game **game)
{
	*game = (t_game *) malloc(sizeof(t_game));
	init_data_header(&(*game)->header);
	init_data_map(&(*game)->map);
	(*game)->file = NULL;
}

void	get_player_position(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->matrix[y][x] == 'N')
			{
				game->player.pos_x = (float)x + 0.5;
				game->player.pos_y = (float)y + 0.5;
				return ;
			}
		}
	}
}

void	init_player(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.cam_plane_x = 0.66;
	game->player.cam_plane_y = 0;
	get_player_position(game);
}
