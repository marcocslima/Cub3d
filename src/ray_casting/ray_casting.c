/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/31 18:40:42 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_casting(t_game *game)
{
	float	d;
	float	ray_length;
	float	ray_angle;
	int		ray_count;

	ray_angle = game->player->angle - (PI/6);
	ray_count = 0;
	while (ray_count < 1)
	{
		ray_length = find_wall_distance(game, ray_angle);
	//	printf("ray_len: %f\n", ray_length);
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
		ray_angle += 0.001;
		ray_count++;
	}
}
