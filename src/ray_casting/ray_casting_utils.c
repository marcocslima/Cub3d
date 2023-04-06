/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:42:55 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/06 09:25:40 by alida-si         ###   ########.fr       */
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

double	hit_wall(t_game *game, double y_coordinate, double x_coordinate,
			double y_step, double x_step)
{
	int	cell_x;
	int	cell_y;

	cell_x = x_coordinate / MAP_CELL;
	cell_y = y_coordinate / MAP_CELL;
	while (cell_x >= 0 && cell_x < game->map->map_width && cell_y >= 0
		&& cell_y < game->map->map_higth
		&& game->map->map[cell_y][cell_x] != '1')
	{
		y_coordinate += y_step;
		x_coordinate += x_step;
		cell_x = x_coordinate / MAP_CELL;
		cell_y = y_coordinate / MAP_CELL;
	}
	return (calculate_ray_length(game, y_coordinate, x_coordinate));
}

int	looking_up(double angle)
{
	if (angle >= PI && angle <= 2 * PI)
		return (1);
	return (0);
}

int	looking_right(double angle)
{
	if (angle > 3 * PI / 2 || angle < PI / 2)
		return (1);
	return (0);
}

double	shorter_distance(double x, double y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}
