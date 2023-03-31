/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_wall_distance.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:39:01 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/30 13:30:56 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	distance_to_vertical_wall_right(t_game *game, float angle)
{
	float	y_coordinate;
	float	x_coordinate;
	float	x_step;
	float	y_step;
	float	ray_length;

	x_coordinate = ((int)game->player->x_position / 40) * 40 + 40;
	y_coordinate = ((int)(game->player->x_position - x_coordinate))
		* (-tan (angle)) + game->player->y_position;
	x_step = 40;
	y_step = 40 * tan(angle);
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}

float	distance_to_vertical_wall_left(t_game *game, float angle)
{
	float	y_coordinate;
	float	x_coordinate;
	float	x_step;
	float	y_step;
	float	ray_length;

	x_coordinate = ((int)game->player->x_position / 40) * 40 - 1;
	y_coordinate = ((int)(game->player->x_position - x_coordinate))
		* (-tan (angle)) + game->player->y_position;
	x_step = -40;
	y_step = 40 * -tan(angle);
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}
