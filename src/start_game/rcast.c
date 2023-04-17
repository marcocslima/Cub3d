/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:01:30 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/17 15:54:36 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_dir(float pixel, t_game **game)
{
	float	multip;
	float	cam_pixel[2];

	multip = 2 * (pixel / WIDTH) - 1;
	cam_pixel[0] = (*game)->player.cam_plane[0] * multip;
	cam_pixel[1] = (*game)->player.cam_plane[1] * multip;
	(*game)->ray.dir_x = (*game)->player.dir_x + cam_pixel[0];
	(*game)->ray.dir_y = (*game)->player.dir_y + cam_pixel[1];
}

void	calc_delta_dist(t_game **game)
{
	(*game)->dists.delta_dist_x = fabs(1 / (*game)->ray.dir_x);
	(*game)->dists.delta_dist_y = fabs(1 / (*game)->ray.dir_y);
	if ((*game)->dists.delta_dist_x > 1000)
	{
		(*game)->dists.delta_dist_x = 1;
		(*game)->dists.delta_dist_y = 0;
	}
	if ((*game)->dists.delta_dist_y > 1000)
	{
		(*game)->dists.delta_dist_x = 0;
		(*game)->dists.delta_dist_y = 1;
	}
}

void	calc_side_dist(t_game **game)
{
	(*game)->dda.map_pos_x = (int)(*game)->player.pos_x;
	(*game)->dda.map_pos_y = (int)(*game)->player.pos_y;
	(*game)->dists.dist_side_x = ((*game)->player.pos_x
			- (float)(*game)->dda.map_pos_x) * (*game)->dists.delta_dist_x;
	(*game)->dda.step_x = -1;
	if ((*game)->ray.dir_x > 0)
	{
		(*game)->dists.dist_side_x = ((float)(*game)->dda.map_pos_x
				+ 1 - (*game)->player.pos_x) * (*game)->dists.delta_dist_x;
		(*game)->dda.step_x = 1;
	}
	(*game)->dists.dist_side_y = ((*game)->player.pos_y
			- (float)(*game)->dda.map_pos_y) * (*game)->dists.delta_dist_y;
	(*game)->dda.step_y = -1;
	if ((*game)->ray.dir_y > 0)
	{
		(*game)->dists.dist_side_y = ((float)(*game)->dda.map_pos_y
				+ 1 - (*game)->player.pos_y) * (*game)->dists.delta_dist_y;
		(*game)->dda.step_y = 1;
	}
}

void	calc_dda(t_game **game)
{
	int	hit;

	hit = FALSE;
	(*game)->dda.dda_line_size_x = (*game)->dists.dist_side_x;
	(*game)->dda.dda_line_size_y = (*game)->dists.dist_side_y;
	(*game)->dda.wall_map_pos_x = (*game)->dda.map_pos_x;
	(*game)->dda.wall_map_pos_y = (*game)->dda.map_pos_y;
	while (hit == FALSE)
	{
		if ((*game)->dda.dda_line_size_x < (*game)->dda.dda_line_size_y)
		{
			(*game)->dda.wall_map_pos_x += (*game)->dda.step_x;
			(*game)->dda.dda_line_size_x += (*game)->dists.delta_dist_x;
			(*game)->dda.hit_side = 0;
		}
		else
		{
			(*game)->dda.wall_map_pos_y += (*game)->dda.step_y;
			(*game)->dda.dda_line_size_y += (*game)->dists.delta_dist_y;
			(*game)->dda.hit_side = 1;
		}
		if ((*game)->map->matrix[(int)(*game)->dda.wall_map_pos_y]
			[(int)(*game)->dda.wall_map_pos_x] == '1')
			hit = TRUE;
	}
}

void	calc_perp_dist(t_game **game)
{
	if ((*game)->dda.hit_side == 0)
	{
		(*game)->dda.perp_dist = ((*game)->dda.wall_map_pos_x
				- (*game)->player.pos_x + ((1 - (*game)->dda.step_x) / 2));
		(*game)->dda.perp_dist /= (*game)->ray.dir_x;
	}
	else
	{
		(*game)->dda.perp_dist = ((*game)->dda.wall_map_pos_y
				- (*game)->player.pos_y + ((1 - (*game)->dda.step_y) / 2));
		(*game)->dda.perp_dist /= (*game)->ray.dir_y;
	}
}
