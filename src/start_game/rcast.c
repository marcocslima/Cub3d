/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:01:30 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/21 16:52:10 by alida-si         ###   ########.fr       */
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

float	calc_mag(float x, float y)
{
	return sqrt(x*x + y*y);
}

int	looking_down(float ray_dir_y)
{
	if (ray_dir_y > 0)
		return (1);
	return (0);
}

int	looking_right(float ray_dir_x)
{
	if (ray_dir_x > 0)
		return (1);
	return (0);
}

void	calc_first_offset_x(t_game **game)
{
	(*game)->dda.first_offset_x = ((*game)->player.pos_x
			- (*game)->dda.map_pos_x) * (*game)->dda.offset_x;
	(*game)->dda.map_step_x = -1;
	if (looking_right((*game)->ray.dir_x))
	{
		(*game)->dda.first_offset_x = ((*game)->dda.map_pos_x
				+ 1 - (*game)->player.pos_x) * (*game)->dda.offset_x;
		(*game)->dda.map_step_x = 1;
	}
}

void	calc_first_offset_y(t_game **game)
{
	(*game)->dda.first_offset_y = ((*game)->player.pos_y
			- (*game)->dda.map_pos_y) * (*game)->dda.offset_y;
	(*game)->dda.map_step_y = -1;
	if (looking_down((*game)->ray.dir_y))
	{
		(*game)->dda.first_offset_y = ((*game)->dda.map_pos_y
				+ 1 - (*game)->player.pos_y) * (*game)->dda.offset_y;
		(*game)->dda.map_step_y = 1;
	}
}

void	get_first_offset(t_game **game)
{
	(*game)->dda.map_pos_x = (int)(*game)->player.pos_x;
	(*game)->dda.map_pos_y = (int)(*game)->player.pos_y;
	calc_first_offset_x(game);
	calc_first_offset_y(game);
}

void	calc_offset(t_game **game)
{
	float	ray_dir_mag;

	ray_dir_mag = calc_mag((*game)->ray.dir_x, (*game)->ray.dir_y);
	(*game)->dda.offset_x = fabs(ray_dir_mag / (*game)->ray.dir_x);
	(*game)->dda.offset_y = fabs(ray_dir_mag / (*game)->ray.dir_y);
	if ((*game)->dda.offset_x > 1000)
	{
		(*game)->dda.offset_x = CELL_SIZE;
		(*game)->dda.offset_y = 0;
	}
	if ((*game)->dda.offset_y > 1000)
	{
		(*game)->dda.offset_x = 0;
		(*game)->dda.offset_y = CELL_SIZE;
	}
}

void	get_offsets(t_game **game)
{
	calc_offset(game);
	get_first_offset(game);
}

int	hit_wall(t_game *game)
{
	if (game->map->matrix[game->dda.map_pos_y][game->dda.map_pos_x] == '1')
		return (1);
	return (0);
}

void	increment_line_size_x(t_game **game)
{
	(*game)->dda.map_pos_x += (*game)->dda.map_step_x;
	(*game)->dda.line_size_x += (*game)->dda.offset_x;
	(*game)->dda.hit_side = VERTICAL;
}

void	increment_line_size_y(t_game **game)
{
	(*game)->dda.map_pos_y += (*game)->dda.map_step_y;
	(*game)->dda.line_size_y += (*game)->dda.offset_y;
	(*game)->dda.hit_side = HORIZONTAL;
}

void	calc_dda(t_game **game)
{
	(*game)->dda.line_size_x = (*game)->dda.first_offset_x;
	(*game)->dda.line_size_y = (*game)->dda.first_offset_y;
	while (hit_wall(*game) == FALSE)
	{
		if ((*game)->dda.line_size_x < (*game)->dda.line_size_y)
			increment_line_size_x(game);
		else
			increment_line_size_y(game);
	}
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
