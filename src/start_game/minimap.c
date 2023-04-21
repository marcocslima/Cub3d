/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/20 23:39:01 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	plot_rays(t_game *game)
{
	int		pixel;
	float	d;

	pixel = -1;
	while (++pixel < WIDTH)
	{
		ray_dir(pixel, &game);
		calc_delta_dist(&game);
		calc_side_dist(&game);
		calc_dda(&game);
		calc_perp_dist(&game);
		calc_wall(&game);
		d = 0.01;
		while (d < 1)
		{
			render_rect(game->img, (t_rect){(game->player.pos_x * 15)
				+ (15 * game->ray.dir_x * d * game->dda.perp_dist),
				(game->player.pos_y * 15)
				+ (15 * game->ray.dir_y * d * game->dda.perp_dist),
				1, 1, GREEN_PIXEL});
			d = d + 0.001;
		}
	}
}

void	render_elements(t_game **game, int i, int j, int side)
{
	int	color;

	color = BLACK_PIXEL;
	if ((*game)->map->matrix[i][j] == '1')
		color = BRICK_PIXEL;
	if ((*game)->map->matrix[i][j] == '0'
		|| (*game)->map->matrix[i][j] == 'N')
		color = BEIGE_PIXEL;
	render_rect((*game)->img, (t_rect){j * side, i * side, side, side, color});
	render_rect((*game)->img, (t_rect){(*game)->player.pos_x
		* side, (*game)->player.pos_y * side, 5, 5, RED_PIXEL});
	render_rect((*game)->img, (t_rect){j * side, i * side, 1,
		side, BLUE_SKY_PIXEL});
	render_rect((*game)->img, (t_rect){j * side, i * side, side,
		1, BLUE_SKY_PIXEL});
}

void	plot_map(t_game *game)
{
	int	i;
	int	j;
	int	side;

	i = -1;
	side = 15;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
			render_elements(&game, i, j, side);
	}
	plot_rays(game);
}
