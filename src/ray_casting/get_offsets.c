/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_offsets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:02:20 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/21 19:04:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
