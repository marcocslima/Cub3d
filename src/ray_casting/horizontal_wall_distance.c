/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall_distance.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:41:15 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/03 10:01:10 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	distance_to_horizontal_wall_up(t_game *game, double angle)
{
	double	y_coordinate;
	double	x_coordinate;
	double	x_step;
	double	y_step;
	double	ray_length;

	y_coordinate = ((int)game->player->y_position / MAP_CELL) * MAP_CELL - 1;
	x_coordinate = ((int)(game->player->y_position - y_coordinate))
			/ (-tan(angle)) + game->player->x_position;
	x_step = MAP_CELL / -tan(angle);
	y_step = -MAP_CELL;
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}

double	distance_to_horizontal_wall_down(t_game *game, double angle)
{
	double	y_coordinate;
	double	x_coordinate;
	double	x_step;
	double	y_step;
	double	ray_length;

	y_coordinate = ((int)game->player->y_position / MAP_CELL) * MAP_CELL + MAP_CELL;
	x_coordinate = (((int)(game->player->y_position - y_coordinate))
			/ (-tan(angle))) + game->player->x_position;
	x_step = MAP_CELL / tan(angle);
	y_step = MAP_CELL;
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}
