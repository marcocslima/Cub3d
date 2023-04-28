/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:24:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/28 07:56:22 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
	(*game)->run = 0;
}
