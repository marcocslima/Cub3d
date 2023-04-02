/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/02 17:34:26 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	deg_to_rad(double degress)
{
	return (degress * (PI/180.0));
}

void render_significant_angles(t_game *game)
{
	float	d;
	float	ray_length;
	float	ray_angle;

	ray_angle = game->player->angle;
	ray_length = find_wall_distance(game, game->player->angle);
	game->player->delta_x = cos(game->player->angle) * ray_length;
	game->player->delta_y = sin(game->player->angle) * ray_length;
	d = 0.001;
	while (d < 1)
	{
		render_rect(game, COLOR_YELLOW, 1, 1,
			game->player->y_position + game->player->delta_y * d,
			game->player->x_position + game->player->delta_x * d);
		d += 0.001;
	}

	ray_angle = game->player->angle - deg_to_rad(30);
	if (ray_angle < 0)
		ray_angle += 2*PI;
	ray_length = find_wall_distance(game, ray_angle);
	game->player->delta_x = cos(ray_angle) * ray_length;
	game->player->delta_y = sin(ray_angle) * ray_length;
	d = 0.001;
	while (d < 1)
	{
		render_rect(game, COLOR_YELLOW, 1, 1,
			game->player->y_position + game->player->delta_y * d,
			game->player->x_position + game->player->delta_x * d);
		d += 0.001;
	}

	ray_angle = game->player->angle + deg_to_rad(30);
	ray_length = find_wall_distance(game, ray_angle);
	game->player->delta_x = cos(ray_angle) * ray_length;
	game->player->delta_y = sin(ray_angle) * ray_length;
	d = 0.001;
	while (d < 1)
	{
		render_rect(game, COLOR_YELLOW, 1, 1,
			game->player->y_position + game->player->delta_y * d,
			game->player->x_position + game->player->delta_x * d);
		d += 0.001;
	}
}

void	ray_casting(t_game *game)
{
	float	d;
	float	ray_length;
	float	ray_angle;
	int		ray_count;

	ray_angle = game->player->angle - deg_to_rad(30);
	if (ray_angle < 0)
		ray_angle += 2*PI;
	ray_count = 0;
	while (ray_count < 900)
	{
		ray_length = find_wall_distance(game, ray_angle);
		game->player->delta_x = cos(ray_angle) * ray_length;
		game->player->delta_y = sin(ray_angle) * ray_length;
		d = 0.001;
		while (d < 1)
		{
			render_rect(game, COLOR_RED, 1, 1,
				game->player->y_position + game->player->delta_y * d,
				game->player->x_position + game->player->delta_x * d);
			d += 0.001;
		}
		ray_angle += deg_to_rad(60)/900;
		ray_count++;
	}
	render_significant_angles(game);
}
