/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:41:37 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/15 18:18:54 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_textures(t_game **game, int pixel)
{
	int	y;
	int	txty;
	int	color;

	if (((*game)->dda.hit_side == 0 && (*game)->ray.dir_x > 0)
		|| ((*game)->dda.hit_side == 1 && (*game)->ray.dir_y < 0))
		(*game)->tx_render.txtx = TILE_SIZE - (*game)->tx_render.txtx - 1;
	(*game)->tx_render.step = 1.0 * TILE_SIZE / (*game)->dda.wall_line_height;
	(*game)->tx_render.txtpos = ((*game)->dda.line_start - HEIGHT / 2
			+ (*game)->dda.wall_line_height / 2) * (*game)->tx_render.step;
	y = (*game)->dda.line_start;
	while (y < (*game)->dda.line_end)
	{
		txty = (int)(*game)->tx_render.txtpos & (TILE_SIZE - 1);
		(*game)->tx_render.txtpos += (*game)->tx_render.step;
		color = (*game)->tx_img[(*game)->tx_render.txt_id].txt_img.data[TILE_SIZE
			* txty + (*game)->tx_render.txtx];
		(*game)->img.data[y * WIDTH + pixel] = color;
		y++;
	}
}

void	run_textures(t_game **game, int pixel)
{
	if ((*game)->dda.hit_side == 0 && (*game)->ray.dir_x >= 0)
		(*game)->tx_render.txt_id = 0;
	if ((*game)->dda.hit_side == 0 && (*game)->ray.dir_x < 0)
		(*game)->tx_render.txt_id = 1;
	if ((*game)->dda.hit_side == 1 && (*game)->ray.dir_y >= 0)
		(*game)->tx_render.txt_id = 2;
	if ((*game)->dda.hit_side == 1 && (*game)->ray.dir_y < 0)
		(*game)->tx_render.txt_id = 3;
	if ((*game)->dda.hit_side == 0)
		(*game)->tx_render.wallx = (*game)->player.pos[1]
			+ (*game)->dda.perp_dist * (*game)->ray.dir_y;
	else
		(*game)->tx_render.wallx = (*game)->player.pos[0]
			+ (*game)->dda.perp_dist * (*game)->ray.dir_x;
	(*game)->tx_render.wallx -= floor((*game)->tx_render.wallx);
	(*game)->tx_render.txtx = (int)((*game)->tx_render.wallx
			* (float)TILE_SIZE);
	render_textures(game, pixel);
}

void	load_textures_continue(t_game *game)
{
	game->tx_img[2].txt_img.img_ptr = mlx_xpm_file_to_image(game->mlx->ptr,
			game->header->we[1], &game->tx_img[2].txt_img.wdt,
			&game->tx_img[2].txt_img.hgt);
	game->tx_img[2].txt_img.data = (int *)mlx_get_data_addr(game->tx_img[2]
			.txt_img.img_ptr, &game->tx_img[2].txt_img.bpp, &game->tx_img[2]
			.txt_img.line_len, &game->tx_img[2].txt_img.endian);
	game->tx_img[3].txt_img.img_ptr = mlx_xpm_file_to_image(game->mlx->ptr,
			game->header->ea[1], &game->tx_img[3].txt_img.wdt,
			&game->tx_img[3].txt_img.hgt);
	game->tx_img[3].txt_img.data = (int *)mlx_get_data_addr(game->tx_img[3]
			.txt_img.img_ptr, &game->tx_img[3].txt_img.bpp, &game->tx_img[3]
			.txt_img.line_len, &game->tx_img[3].txt_img.endian);
}

void	load_textures(t_game *game)
{
	game->tx_img[0].txt_img.img_ptr = mlx_xpm_file_to_image(game->mlx->ptr,
			game->header->no[1], &game->tx_img[0].txt_img.wdt,
			&game->tx_img[0].txt_img.hgt);
	game->tx_img[0].txt_img.data = (int *)mlx_get_data_addr(game->tx_img[0]
			.txt_img.img_ptr, &game->tx_img[0].txt_img.bpp, &game->tx_img[0]
			.txt_img.line_len, &game->tx_img[0].txt_img.endian);
	game->tx_img[1].txt_img.img_ptr = mlx_xpm_file_to_image(game->mlx->ptr,
			game->header->so[1], &game->tx_img[1].txt_img.wdt,
			&game->tx_img[1].txt_img.hgt);
	game->tx_img[1].txt_img.data = (int *)mlx_get_data_addr(game->tx_img[1]
			.txt_img.img_ptr, &game->tx_img[1].txt_img.bpp, &game->tx_img[1]
			.txt_img.line_len, &game->tx_img[1].txt_img.endian);
	load_textures_continue(game);
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
