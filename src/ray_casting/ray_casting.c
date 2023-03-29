/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/29 13:39:26 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_casting(t_game *game)
{
	float	d = 0.1;
	int		ray_length;

	ray_length = find_wall_distance(game);
	game->player->delta_x = cos(game->player->angle) * ray_length;
	game->player->delta_y = sin(game->player->angle) * ray_length;

	while(d < 1)
	{
		render_rect(game, COLOR_RED, 1, 1, game->player->y_position + game->player->delta_y * d, game->player->x_position + game->player->delta_x * d);
		d += 0.001;
	}
}
