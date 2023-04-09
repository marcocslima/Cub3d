/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/09 16:02:02 by mcesar-d         ###   ########.fr       */
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

void	plot_rays(t_data *data)
{
	int		pixel;
	float	d;

	pixel = -1;
	while (++pixel < WIDTH)
	{
		ray_dir(pixel, data);
		calc_delta_dist(data);
		calc_side_dist(data);
		calc_dda(data);
		calc_perp_dist(data);
		calc_wall(data);
		d = 0.01;
		while (d < 1)
		{
			render_rect(&data->img, (t_rect){(data->gm->player.pos[0] * 15)
				+ (15 * data->gm->ray.dir_x * d * data->gm->dda.perp_dist),
				(data->gm->player.pos[1] * 15)
				+ (15 * data->gm->ray.dir_y * d * data->gm->dda.perp_dist),
				1, 1, GREEN_PIXEL});
			d = d + 0.001;
		}
	}
}

void	render_elements(t_data *data, int i, int j, int side)
{
	int	color;

	color = BLACK_PIXEL;
	if (data->gm->map->map[i][j] == '1')
		color = BRICK_PIXEL;
	if (data->gm->map->map[i][j] == '0'
		|| data->gm->map->map[i][j] == 'N')
		color = BEIGE_PIXEL;
	render_rect(&data->img, (t_rect){j * side, i * side, side, side, color});
	render_rect(&data->img, (t_rect){data->gm->player.pos[0]
		* side, data->gm->player.pos[1] * side, 5, 5, RED_PIXEL});
	render_rect(&data->img, (t_rect){j * side, i * side, 1,
		side, BLUE_SKY_PIXEL});
	render_rect(&data->img, (t_rect){j * side, i * side, side,
		1, BLUE_SKY_PIXEL});
}

void	plot_map(t_data *data)
{
	int	i;
	int	j;
	int	side;

	i = -1;
	side = 15;
	while (++i < data->gm->map->map_higth)
	{
		j = -1;
		while (++j < data->gm->map->map_width)
			render_elements(data, i, j, side);
	}
	plot_rays(data);
}
