/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:45:33 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 15:01:20 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_perp_dist(t_game **game)
{
	if ((*game)->dda.hit_side == VERTICAL)
	{
		(*game)->dda.perp_dist = ((*game)->dda.map_pos_x
				- (*game)->player.pos_x + ((1 - (*game)->dda.map_step_x) / 2));
		(*game)->dda.perp_dist /= (*game)->ray.dir_x;
	}
	else
	{
		(*game)->dda.perp_dist = ((*game)->dda.map_pos_y
				- (*game)->player.pos_y + ((1 - (*game)->dda.map_step_y) / 2));
		(*game)->dda.perp_dist /= (*game)->ray.dir_y;
	}
}

void	ray_dir(float pixel, t_game **game)
{
	float	multip;
	float	cam_pixel_x;
	float	cam_pixel_y;

	multip = 2 * (pixel / WIDTH) - 1;
	cam_pixel_x = (*game)->player.cam_plane_x * multip;
	cam_pixel_y = (*game)->player.cam_plane_y * multip;
	(*game)->ray.dir_x = (*game)->player.dir_x + cam_pixel_x;
	(*game)->ray.dir_y = (*game)->player.dir_y + cam_pixel_y;
}

void	calc_wall_height(t_game **game)
{
	(*game)->dda.wall_line_height = HEIGHT / (*game)->dda.perp_dist;
	(*game)->dda.wall_first_pixel = HEIGHT / 2
				- (*game)->dda.wall_line_height / 2;
	if ((*game)->dda.wall_first_pixel < 0)
		(*game)->dda.wall_first_pixel = 0;
	(*game)->dda.wall_last_pixel = (*game)->dda.wall_line_height
				/ 2 + HEIGHT / 2;
	if ((*game)->dda.wall_last_pixel >= HEIGHT)
		(*game)->dda.wall_last_pixel = HEIGHT - 1;
}

void	ray_casting(t_game *game)
{
	float	pixel;

	pixel = -1;
	while (++pixel < WIDTH)
	{
		ray_dir(pixel, &game);
		get_offsets(&game);
		calc_dda(&game);
		calc_perp_dist(&game);
		calc_wall_height(&game);
		render_textured_walls(game, pixel);
	}
}
