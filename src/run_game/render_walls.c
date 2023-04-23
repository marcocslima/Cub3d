/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:41:37 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/23 15:33:00 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	get_wall_x_coordinate(t_game *game)
{
	float	wall_x;

	if (game->dda.hit_side == VERTICAL)
		wall_x = game->player.pos_y
			+ game->dda.perp_dist * game->ray.dir_y;
	else
		wall_x = game->player.pos_x
			+ game->dda.perp_dist * game->ray.dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_x_coordinate(t_game *game)
{
	int		txt_pixel_x;
	float	wall_x;

	wall_x = get_wall_x_coordinate(game);
	txt_pixel_x = (int)(wall_x * (float)TILE_SIZE);
	return (txt_pixel_x);
}

int	get_txt_color(int *texture_img_data, int txt_pixel_x, int txt_pixel_y)
{
	return (texture_img_data[TILE_SIZE * txt_pixel_y + txt_pixel_x]);
}

void	put_texture(t_game *game, int wall_pixel_x, int *texture_img_data)
{
	int		wall_pixel_y;
	int		txt_pixel_y;
	int		txt_pixel_x;
	float	txt_first_pixel;
	float	step;

	txt_pixel_x = get_texture_x_coordinate(game);
	step = 1.0 * TILE_SIZE / game->dda.wall_line_height;
	txt_first_pixel = (game->dda.wall_first_pixel - HEIGHT / 2
			+ game->dda.wall_line_height / 2) * step;
	wall_pixel_y = game->dda.wall_first_pixel;
	while (wall_pixel_y < game->dda.wall_last_pixel)
	{
		txt_pixel_y = (int)txt_first_pixel & (TILE_SIZE - 1);
		txt_first_pixel += step;
		img_pix_put(game->img, wall_pixel_x, wall_pixel_y,
			get_txt_color(texture_img_data, txt_pixel_x, txt_pixel_y));
		wall_pixel_y++;
	}
}

void	render_textured_walls(t_game *game, int pixel)
{
	if (game->dda.hit_side == VERTICAL)
	{
		if (looking_left(game->ray.dir_x))
			put_texture(game, pixel, game->texture_img->we->data);
		else
			put_texture(game, pixel, game->texture_img->ea->data);
	}
	if (game->dda.hit_side == HORIZONTAL)
	{
		if (looking_up(game->ray.dir_y))
			put_texture(game, pixel, game->texture_img->no->data);
		else
			put_texture(game, pixel, game->texture_img->so->data);
	}
}
