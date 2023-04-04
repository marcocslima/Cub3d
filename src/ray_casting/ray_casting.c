/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/04 18:54:31 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	deg_to_rad(double degress)
{
	return (degress * (PI/180.0));
}

void render_significant_angles(t_game *game)
{
	double	d;
	double	ray_length;
	double	ray_angle;

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

void	draw_line(double x1, double y1, double y2, t_game *game)
{
	int	i = 0;

	while (y1 < y2)
	{
		render_rect(game, game->wall_color, 1, 1, y1, x1);
		y1++;
	}
}

void	ray_casting(t_game *game)
{
	double	d;
	double	ray_length;
	double	ray_angle;
	double	distance;
	double	correc_wall_distance;
	double	distance_to_proj_plane;
	double	wall_height;
	int		ray_count;

	ray_angle = game->player->angle - deg_to_rad(30);
	if (ray_angle < 0)
		ray_angle += 2*PI;
	ray_count = 0;
	while (ray_count < 900)
	{
		ray_length = find_wall_distance(game, ray_angle);

		//distance = ray_length * cos(ray_angle - game->player->angle);
		// wall_height = ((600/2) / distance) * 60;
		// draw_line(ray_count, (600/2)- wall_height, (600/2)+ wall_height, game);
		distance_to_proj_plane = (900/2) / tan(deg_to_rad(60)/2);
		correc_wall_distance = ray_length * cos(ray_angle - game->player->angle);
		distance = (MAP_CELL / correc_wall_distance) * distance_to_proj_plane;
		//wall_height = (MAP_CELL/ray_length) * distance;
		draw_line(ray_count, (600/2)- (distance/2), (600/2)+ (distance/2), game);

		// game->player->delta_x = cos(ray_angle) * ray_length;
		// game->player->delta_y = sin(ray_angle) * ray_length;
		// d = 0.001;
		// while (d < 1)
		// {
		// 	render_rect(game, COLOR_RED, 1, 1,
		// 		game->player->y_position + game->player->delta_y * d,
		// 		game->player->x_position + game->player->delta_x * d);
		// 	d += 0.001;
		// }
		ray_angle += deg_to_rad(60)/900;
		ray_count++;
	}
	//render_significant_angles(game);
}
