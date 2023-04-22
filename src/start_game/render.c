/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:41:37 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/22 14:50:28 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_textures(t_game **game, int pixel, int *img_data)
{
	int	y;
	int	txty;
	int	color;

	if (((*game)->dda.hit_side == VERTICAL && (*game)->ray.dir_x > 0)
		|| ((*game)->dda.hit_side == HORIZONTAL && (*game)->ray.dir_y < 0))
		(*game)->tx_render.txtx = TILE_SIZE - (*game)->tx_render.txtx - 1;
	(*game)->tx_render.step = 1.0 * TILE_SIZE / (*game)->dda.wall_line_height;
	(*game)->tx_render.txtpos = ((*game)->dda.line_start - HEIGHT / 2
			+ (*game)->dda.wall_line_height / 2) * (*game)->tx_render.step;
	y = (*game)->dda.line_start;
	while (y < (*game)->dda.line_end)
	{
		txty = (int)(*game)->tx_render.txtpos & (TILE_SIZE - 1);
		(*game)->tx_render.txtpos += (*game)->tx_render.step;
		color = img_data[TILE_SIZE * txty + (*game)->tx_render.txtx];
		(*game)->img->data[y * WIDTH + pixel] = color;
		y++;
	}
}

void	run_textures(t_game **game, int pixel)
{
	if ((*game)->dda.hit_side == VERTICAL)
		(*game)->tx_render.wallx = (*game)->player.pos_y
			+ (*game)->dda.perp_dist * (*game)->ray.dir_y;
	else
		(*game)->tx_render.wallx = (*game)->player.pos_x
			+ (*game)->dda.perp_dist * (*game)->ray.dir_x;
	(*game)->tx_render.wallx -= floor((*game)->tx_render.wallx);
	(*game)->tx_render.txtx = (int)((*game)->tx_render.wallx
			* (float)TILE_SIZE);
	if ((*game)->dda.hit_side == VERTICAL)
	{
		if ((*game)->ray.dir_x >= 0)
			render_textures(game, pixel, (*game)->texture_img->ea->data);
		if ((*game)->ray.dir_x < 0)
			render_textures(game, pixel, (*game)->texture_img->we->data);
	}
	if ((*game)->dda.hit_side == HORIZONTAL)
	{
		if ((*game)->ray.dir_y >= 0)
			render_textures(game, pixel, (*game)->texture_img->so->data);
		if ((*game)->ray.dir_y < 0)
			render_textures(game, pixel, (*game)->texture_img->no->data);
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
