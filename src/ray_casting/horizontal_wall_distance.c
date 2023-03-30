/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall_distance.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:41:15 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/30 13:10:02 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	distance_to_horizontal_wall_up(t_game *game, float angle)
{
	int	y_coordinate;
	int	x_coordinate;
	int	x_step;
	int	y_step;
	int	ray_length;

	y_coordinate = ((int)game->player->y_position / 40) * 40 - 1;
	x_coordinate = ((int)(game->player->y_position - y_coordinate)
			/ (-tan(angle))) + game->player->x_position;
	x_step = 40 / -tan(angle);
	y_step = -40;
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}

int	distance_to_horizontal_wall_down(t_game *game, float angle)
{
	int	y_coordinate;
	int	x_coordinate;
	int	x_step;
	int	y_step;
	int	ray_length;

	y_coordinate = ((int)game->player->y_position / 40) * 40 + 40;
	x_coordinate = ((int)(game->player->y_position - y_coordinate)
			/ (-tan(angle))) + game->player->x_position;
	x_step = 40 / tan(angle);
	y_step = 40;
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}
