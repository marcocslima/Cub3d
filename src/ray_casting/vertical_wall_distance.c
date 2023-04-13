/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_wall_distance.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:39:01 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/13 12:09:19 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	x_intersection(t_game *game)
{
	double	player_x_posit;

	player_x_posit = game->player->x_position;
	if (looking_right(game->ray->angle))
		return (((int)player_x_posit / MAP_CELL) * MAP_CELL + MAP_CELL);
	return (((int)player_x_posit / MAP_CELL) * MAP_CELL - 0.0001);
}

static double	y_intersection(t_game *game)
{
	double	player_x_posit;
	double	player_y_posit;
	double	x_intersection;
	double	angle;

	player_x_posit = game->player->x_position;
	player_y_posit = game->player->y_position;
	x_intersection = game->ray_tmp->x_intersection;
	angle = game->ray->angle;
	return (((int)(player_x_posit - x_intersection))
			* (-tan (angle)) + player_y_posit);
}

void	distance_to_vertical_wall_right(t_game **game)
{
	(*game)->ray_tmp->x_intersection = x_intersection(*game);
	(*game)->ray_tmp->y_intersection = y_intersection(*game);
	(*game)->ray_tmp->x_step = MAP_CELL;
	(*game)->ray_tmp->y_step = MAP_CELL * tan((*game)->ray->angle);
	hit_wall(game);
	get_ray_data(game, VERTICAL);
}

void	distance_to_vertical_wall_left(t_game **game)
{
	(*game)->ray_tmp->x_intersection = x_intersection(*game);
	(*game)->ray_tmp->y_intersection = y_intersection(*game);
	(*game)->ray_tmp->x_step = -MAP_CELL;
	(*game)->ray_tmp->y_step = MAP_CELL * -tan((*game)->ray->angle);
	hit_wall(game);
	get_ray_data(game, VERTICAL);
}
