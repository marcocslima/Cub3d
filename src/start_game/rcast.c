/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:01:30 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/20 06:10:47 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_dir(float pixel, t_data *data)
{
	float	multip;
	float	cam_pixel[2];

	multip = 2 * (pixel / WIDTH) - 1;
	cam_pixel[0] = data->gm->player.cam_plane[0] * multip;
	cam_pixel[1] = data->gm->player.cam_plane[1] * multip;
	data->gm->ray.dir_x = data->gm->player.dir[0] + cam_pixel[0];
	data->gm->ray.dir_y = data->gm->player.dir[1] + cam_pixel[1];
	if (data->gm->ray.dir_x == 0)
	{
		data->gm->dists.delta_dist_x = 1;
		data->gm->dists.delta_dist_y = 0;
	}
	else
		if(data->gm->ray.dir_y)
			data->gm->dists.delta_dist_x = fabs(1 / data->gm->ray.dir_x);
	if (data->gm->ray.dir_y == 0)
	{
		data->gm->dists.delta_dist_x = 0;
		data->gm->dists.delta_dist_y = 1;
	}
	else
		if(data->gm->ray.dir_x)
			data->gm->dists.delta_dist_y = fabs(1 / data->gm->ray.dir_y);
}

void	calc_side_dist(t_data *data)
{
	data->gm->dda.map_pos_x = floor(data->gm->player.pos[0]);
	data->gm->dda.map_pos_y = floor(data->gm->player.pos[1]);
	if(data->gm->ray.dir_x < 0)
	{
		data->gm->dists.dist_side_x = (data->gm->player.pos[0] - data->gm->dda.map_pos_x) * data->gm->dists.delta_dist_x;
		data->gm->dda.step_x = -1;
	}
	else
	{
		data->gm->dists.dist_side_x = (data->gm->dda.map_pos_x + 1 - data->gm->player.pos[0]) * data->gm->dists.delta_dist_x;
		data->gm->dda.step_x = 1;
	}
	if(data->gm->ray.dir_y < 0)
	{
		data->gm->dists.dist_side_y = (data->gm->player.pos[1] - data->gm->dda.map_pos_y) * data->gm->dists.delta_dist_y;
		data->gm->dda.step_y = -1;
	}
	else
	{
		data->gm->dists.dist_side_y = (data->gm->dda.map_pos_y + 1 - data->gm->player.pos[1]) * data->gm->dists.delta_dist_y;
		data->gm->dda.step_y = 1;
	}
}

void	calc_dda(t_data *data)
{
	int	hit;

	hit = 0;
	data->gm->dda.ddaLineSizeX = data->gm->dists.dist_side_x;
	data->gm->dda.ddaLineSizeY = data->gm->dists.dist_side_y;
	data->gm->dda.wall_map_pos_x = data->gm->player.pos[0];
	data->gm->dda.wall_map_pos_y = data->gm->player.pos[1];
	while(hit == 0)
	{
		if(data->gm->dda.ddaLineSizeX < data->gm->dda.ddaLineSizeY)
		{
			data->gm->dda.wall_map_pos_x += data->gm->dda.step_x;
			data->gm->dda.ddaLineSizeX += data->gm->dists.delta_dist_x;
			data->gm->dda.hitSide = 0;
		}
		else
		{
			data->gm->dda.wall_map_pos_y += data->gm->dda.step_y;
			data->gm->dda.ddaLineSizeY += data->gm->dists.delta_dist_y;
			data->gm->dda.hitSide = 1;
		}
		if(data->gm->map->map[(int)floor(data->gm->dda.wall_map_pos_x)][(int)floor(data->gm->dda.wall_map_pos_y)] == '1')
			hit = 1;
	}
}

void	calc_perp_dist(t_data *data)
{
	if (data->gm->dda.hitSide == 0)
	{
		data->gm->dda.perp_dist = fabs(data->gm->dda.wall_map_pos_x - data->gm->player.pos[0] +
			(((1-data->gm->dda.step_x)/2) / data->gm->ray.dir_x));
	}
	else
	{
		data->gm->dda.perp_dist = fabs(data->gm->dda.wall_map_pos_y - data->gm->player.pos[1] +
			(((1-data->gm->dda.step_y)/2) / data->gm->ray.dir_y));
	}
}

void	calc_wall(t_data *data)
{
	data->gm->dda.wall_line_height = HEIGHT / data->gm->dda.perp_dist;
	data->gm->dda.line_start = HEIGHT / 2 - data->gm->dda.wall_line_height / 2;
	data->gm->dda.line_end = HEIGHT / 2 + data->gm->dda.wall_line_height / 2;
}