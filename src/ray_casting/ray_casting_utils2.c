/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:49:51 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/13 11:59:16 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	calculate_ray_length(t_game *game)
{
	double	delta_y;
	double	delta_x;

	delta_y = game->player->y_position - game->ray_tmp->y_intersection;
	delta_x = game->player->x_position - game->ray_tmp->x_intersection;
	return (sqrt(pow(delta_y, 2) + pow(delta_x, 2)));
}

void	hit_wall(t_game **game)
{
	int	cell_x;
	int	cell_y;

	cell_x = (*game)->ray_tmp->x_intersection / MAP_CELL;
	cell_y = (*game)->ray_tmp->y_intersection / MAP_CELL;
	while (cell_x >= 0 && cell_x < (*game)->map->map_width && cell_y >= 0
		&& cell_y < (*game)->map->map_higth
		&& (*game)->map->map[cell_y][cell_x] != '1')
	{
		(*game)->ray_tmp->y_intersection += (*game)->ray_tmp->y_step;
		(*game)->ray_tmp->x_intersection += (*game)->ray_tmp->x_step;
		cell_x = (*game)->ray_tmp->x_intersection / MAP_CELL;
		cell_y = (*game)->ray_tmp->y_intersection / MAP_CELL;
	}
	(*game)->ray_tmp->ray_length = calculate_ray_length(*game);
}

void	get_ray_data(t_game **game, int wall_plane)
{
	if ((*game)->ray->length == 0)
	{
		(*game)->ray->length = (*game)->ray_tmp->ray_length;
		(*game)->ray->x_intersection = (*game)->ray_tmp->x_intersection;
		(*game)->ray->y_intersection = (*game)->ray_tmp->y_intersection;
		(*game)->ray->wall_plane = wall_plane;
	}
	else if ((*game)->ray_tmp->ray_length < (*game)->ray->length)
	{
		(*game)->ray->length = (*game)->ray_tmp->ray_length;
		(*game)->ray->x_intersection = (*game)->ray_tmp->x_intersection;
		(*game)->ray->y_intersection = (*game)->ray_tmp->y_intersection;
		(*game)->ray->wall_plane = wall_plane;
	}
}
