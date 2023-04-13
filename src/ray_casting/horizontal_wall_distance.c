/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall_distance.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:41:15 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/13 12:09:44 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	y_intersection(t_game *game)
{
	double	player_y_posit;

	player_y_posit = game->player->y_position;
	if (looking_up(game->ray->angle))
		return (((int)player_y_posit / MAP_CELL) * MAP_CELL - 0.0001);
	return (((int)player_y_posit / MAP_CELL) * MAP_CELL + MAP_CELL);
}

static double	x_intersection(t_game *game)
{
	double	player_x_posit;
	double	player_y_posit;
	double	y_intersection;
	double	angle;

	player_x_posit = game->player->x_position;
	player_y_posit = game->player->y_position;
	y_intersection = game->ray_tmp->y_intersection;
	angle = game->ray->angle;
	return (((int)(player_y_posit - y_intersection))
			/ (-tan(angle)) + player_x_posit);
}

void	distance_to_horizontal_wall_up(t_game **game)
{
	double	ray_length;

	(*game)->ray_tmp->y_intersection = y_intersection(*game);
	(*game)->ray_tmp->x_intersection = x_intersection(*game);
	(*game)->ray_tmp->x_step = MAP_CELL / -tan((*game)->ray->angle);
	(*game)->ray_tmp->y_step = -MAP_CELL;
	hit_wall(game);
	get_ray_data(game, HORIZONTAL);
}

void	distance_to_horizontal_wall_down(t_game **game)
{
	(*game)->ray_tmp->y_intersection = y_intersection(*game);
	(*game)->ray_tmp->x_intersection = x_intersection(*game);
	(*game)->ray_tmp->x_step = MAP_CELL / tan((*game)->ray->angle);
	(*game)->ray_tmp->y_step = MAP_CELL;
	hit_wall(game);
	get_ray_data(game, HORIZONTAL);
}
