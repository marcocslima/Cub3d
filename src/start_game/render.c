/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:41:37 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/23 13:35:36 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	get_wall_x_coordinate(t_game **game)
{
	float	wall_x;

	if ((*game)->dda.hit_side == VERTICAL)
		wall_x = (*game)->player.pos_y
			+ (*game)->dda.perp_dist * (*game)->ray.dir_y;
	else
		wall_x = (*game)->player.pos_x
			+ (*game)->dda.perp_dist * (*game)->ray.dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_x_coordinate(t_game **game)
{
	int		txt_pixel_x;
	float	wall_x;

	wall_x = get_wall_x_coordinate(game);
	txt_pixel_x = (int)(wall_x * (float)TILE_SIZE);
	return (txt_pixel_x);
}

void	render_textures(t_game **game, int wall_pixel_x, int *texture_img_data)
{
	int	wall_pixel_y;
	int	txt_pixel_y;
	int	txt_pixel_x;
	int	color;

	txt_pixel_x = get_texture_x_coordinate(game);
	(*game)->tx_render.step = 1.0 * TILE_SIZE / (*game)->dda.wall_line_height;
	(*game)->tx_render.txtpos = ((*game)->dda.line_start - HEIGHT / 2
			+ (*game)->dda.wall_line_height / 2) * (*game)->tx_render.step;
	wall_pixel_y = (*game)->dda.line_start;
	while (wall_pixel_y < (*game)->dda.line_end)
	{
		txt_pixel_y = (int)(*game)->tx_render.txtpos & (TILE_SIZE - 1);
		(*game)->tx_render.txtpos += (*game)->tx_render.step;
		color = texture_img_data[TILE_SIZE * txt_pixel_y + txt_pixel_x];
		img_pix_put((*game)->img, wall_pixel_x, wall_pixel_y, color);
		wall_pixel_y++;
	}
}

int	looking_left(float ray_dir_x)
{
	if (ray_dir_x < 0)
		return (1);
	return (0);
}

int	looking_up(float ray_dir_y)
{
	if (ray_dir_y < 0)
		return (1);
	return (0);
}

void	run_textures(t_game **game, int pixel)
{
	if ((*game)->dda.hit_side == VERTICAL)
	{
		if (looking_left((*game)->ray.dir_x))
			render_textures(game, pixel, (*game)->texture_img->we->data);
		else
			render_textures(game, pixel, (*game)->texture_img->ea->data);
	}
	if ((*game)->dda.hit_side == HORIZONTAL)
	{
		if (looking_up((*game)->ray.dir_y))
			render_textures(game, pixel, (*game)->texture_img->no->data);
		else
			render_textures(game, pixel, (*game)->texture_img->so->data);
	}
}

void	calc_wall(t_game **game)
{
	(*game)->dda.wall_line_height = HEIGHT / (*game)->dda.perp_dist;
	(*game)->dda.line_start = HEIGHT / 2 - (*game)->dda.wall_line_height / 2;
	if ((*game)->dda.line_start < 0)
		(*game)->dda.line_start = 0;
	(*game)->dda.line_end = (*game)->dda.wall_line_height / 2 + HEIGHT / 2;
	if ((*game)->dda.line_end >= HEIGHT)
		(*game)->dda.line_end = HEIGHT - 1;
}
