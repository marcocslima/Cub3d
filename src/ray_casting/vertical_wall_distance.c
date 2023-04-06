/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_wall_distance.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:39:01 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/06 10:43:32 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	distance_to_vertical_wall_right(t_game **game)
{
	double	y_coordinate;
	double	x_coordinate;
	double	x_step;
	double	y_step;
	double	ray_length;

	x_coordinate = ((int)(*game)->player->x_position / MAP_CELL) * MAP_CELL + MAP_CELL;
	y_coordinate = ((int)((*game)->player->x_position - x_coordinate))
		* (-tan ((*game)->ray->angle)) + (*game)->player->y_position;
	x_step = MAP_CELL;
	y_step = MAP_CELL * tan((*game)->ray->angle);
	ray_length = hit_wall(*game, &y_coordinate, &x_coordinate, y_step, x_step);
	if ((*game)->ray->length == 0)
		(*game)->ray->length = ray_length;
	else if (ray_length < (*game)->ray->length)
	{
		(*game)->ray->length = ray_length;
		(*game)->ray->x_coordinate = x_coordinate;
		(*game)->ray->y_coordinate = y_coordinate;
	}
	return (ray_length);
}

double	distance_to_vertical_wall_left(t_game **game)
{
	double	y_coordinate;
	double	x_coordinate;
	double	x_step;
	double	y_step;
	double	ray_length;

	x_coordinate = ((int)(*game)->player->x_position / MAP_CELL) * MAP_CELL - 0.0001;
	y_coordinate = ((int)((*game)->player->x_position - x_coordinate))
		* (-tan ((*game)->ray->angle)) + (*game)->player->y_position;
	x_step = -MAP_CELL;
	y_step = MAP_CELL * -tan((*game)->ray->angle);
	ray_length = hit_wall(*game, &y_coordinate, &x_coordinate, y_step, x_step);
	if ((*game)->ray->length == 0)
		(*game)->ray->length = ray_length;
	else if (ray_length < (*game)->ray->length)
	{
		(*game)->ray->length = ray_length;
		(*game)->ray->x_coordinate = x_coordinate;
		(*game)->ray->y_coordinate = y_coordinate;
	}
	return (ray_length);
}
