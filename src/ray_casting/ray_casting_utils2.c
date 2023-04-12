/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:49:51 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/12 15:54:05 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	calculate_ray_length(t_game *game, double y_coordinate, double x_coordinate)
{
	double	delta_y;
	double	delta_x;

	delta_y = game->player->y_position - y_coordinate;
	delta_x = game->player->x_position - x_coordinate;
	return (sqrt(pow(delta_y, 2) + pow(delta_x, 2)));
}

double	hit_wall(t_game *game, double *y_coordinate, double *x_coordinate,
			double y_step, double x_step)
{
	int	cell_x;
	int	cell_y;

	cell_x = *x_coordinate / MAP_CELL;
	cell_y = *y_coordinate / MAP_CELL;
	while (cell_x >= 0 && cell_x < game->map->map_width && cell_y >= 0
		&& cell_y < game->map->map_higth
		&& game->map->map[cell_y][cell_x] != '1')
	{
		*y_coordinate += y_step;
		*x_coordinate += x_step;
		cell_x = *x_coordinate / MAP_CELL;
		cell_y = *y_coordinate / MAP_CELL;
	}
	return (calculate_ray_length(game, *y_coordinate, *x_coordinate));
}

void	get_ray_data(t_game **game, double x_coordinate, double y_coordinate,
			double ray_length)
{
	if ((*game)->ray->length == 0)
	{
		(*game)->ray->length = ray_length;
		(*game)->ray->x_coordinate = x_coordinate;
		(*game)->ray->y_coordinate = y_coordinate;
	}
	else if (ray_length < (*game)->ray->length)
	{
		(*game)->ray->length = ray_length;
		(*game)->ray->x_coordinate = x_coordinate;
		(*game)->ray->y_coordinate = y_coordinate;
	}
}
