/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:24:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/11 22:56:42 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	(*map)->map_higth = 0;
	(*map)->map_width = 0;
	(*map)->init_map = 0;
	(*map)->map = NULL;
}

void	init_player(t_player **player)
{
	*player = (t_player *) malloc(sizeof(t_player));
	(*player)->y_position = 0;
	(*player)->x_position = 0;
	(*player)->angle = 2 * PI;
	(*player)->delta_x = 0;
	(*player)->delta_y = 0;
}

void	init_ray(t_ray_casting **ray)
{
	*ray = (t_ray_casting *) malloc(sizeof(t_ray_casting));
	(*ray)->wall_plane = -1;
	(*ray)->x_coordinate = 0;
	(*ray)->y_coordinate = 0;
	(*ray)->length = 0;
}

void	init_data(t_game **game)
{
	*game = (t_game *) malloc(sizeof(t_game));
	(*game)->mlx_data = NULL;
	init_data_header(&(*game)->header);
	init_data_map(&(*game)->map);
	init_data_img(&(*game)->img_data);
	init_player(&(*game)->player);
	init_ray(&(*game)->ray);
	init_data_texture_img(&(*game)->texture_img);
}
