/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:01:30 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/22 01:51:13 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
