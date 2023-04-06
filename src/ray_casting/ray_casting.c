/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/06 10:32:31 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	deg_to_rad(double degress)
{
	return (degress * (PI/180.0));
}

void	draw_line(double x1, double y1, double y2, t_game *game)
{
	int	i = 0;

	while (y1 < y2)
	{
		render_rect(game, game->ray->wall_color, 1, 1, y1, x1);
		y1++;
	}
}

void	put_texture(t_game *game)
{
	int	offset;

	if (game->ray->wall_plane == VERTICAL)
		printf("vertical\n");
	else if (game->ray->wall_plane == HORIZONTAL)
		offset = game->ray->x_coordinate - ((int)(game->ray->x_coordinate / 64) * 64);
}

void	ray_casting(t_game *game)
{
	//double	d;
	// double	ray_length;
	// double	ray_angle;
	double	distance;
	double	correc_wall_distance;
	double	distance_to_proj_plane;
	double	wall_height;
	// int		ray_count;
	//t_ray_casting	*ray;

	game->ray->angle = game->player->angle - deg_to_rad(30);
	if (game->ray->angle < 0)
		game->ray->angle += 2*PI;
	game->ray->id = 0;
	while (game->ray->id < 900)
	{
		game->ray->length = 0;
		find_wall_distance(&game);
		//distance = ray_length * cos(game->ray->angle - game->player->angle);
		// wall_height = ((600/2) / distance) * 60;
		// draw_line(game->ray->id, (600/2)- wall_height, (600/2)+ wall_height, game);
		distance_to_proj_plane = (900/2) / tan(deg_to_rad(60)/2);
		correc_wall_distance = game->ray->length * cos(game->ray->angle - game->player->angle);
		distance = (MAP_CELL / correc_wall_distance) * distance_to_proj_plane;
		//wall_height = (MAP_CELL/ray_length) * distance;
		draw_line(game->ray->id, (600/2)- (distance/2), (600/2)+ (distance/2), game);
		//put_texture(game);
		game->ray->angle += deg_to_rad(60)/900;
		game->ray->id++;
	}
}
