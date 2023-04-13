/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/13 14:20:22 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	calculate_wall_height(t_game *game)
{
	double	correc_wall_distance;
	double	distance_to_proj_plane;
	double	wall_height;

	distance_to_proj_plane = (WINDOW_WIDTH / 2)
		/ tan(deg_to_rad(FOV_ANGLE) / 2);
	correc_wall_distance = game->ray->length
		* cos(game->ray->angle - game->player->angle);
	wall_height = (MAP_CELL / correc_wall_distance) * distance_to_proj_plane;
	return (wall_height);
}

void	ray_casting(t_game *game)
{
	double	wall_height;

	game->ray->angle = game->player->angle - deg_to_rad(FOV_ANGLE / 2);
	if (game->ray->angle < 0)
		game->ray->angle += 2 * PI;
	game->ray->id = 0;
	while (game->ray->id < WINDOW_WIDTH)
	{
		game->ray->length = 0;
		game->ray_tmp->ray_length = 0;
		find_wall_distance(&game);
		wall_height = calculate_wall_height(game);
		render_wall((WINDOW_HEIGHT / 2) - (wall_height / 2), game, wall_height);
		game->ray->angle += deg_to_rad(FOV_ANGLE) / WINDOW_WIDTH;
		game->ray->id++;
	}
}
