/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/07 07:59:17 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

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

void	render_background(t_img *img, int cceil, int cflor)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			img_pix_put(img, j++, i, cflor);
	}
	i = -1;
	while (++i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
			img_pix_put(img, j++, i, cceil);
	}
}

void	plot_rays(t_data *data)
{
	int	pixel;
	
	pixel = -1;
	while (++pixel < WIDTH)
	{
		float	d;

		ray_dir(pixel, data);
		calc_delta_dist(data);
		calc_side_dist(data);
		calc_dda(data);
		calc_perp_dist(data);
		calc_wall(data);
		d = 0.01;
		while(d < 1)
		{
			render_rect(&data->img, (t_rect){(data->gm->player.pos[0] * 15) + 
				(15 * data->gm->ray.dir_x * d * data->gm->dda.perp_dist),
				(data->gm->player.pos[1] * 15) + 
				(15 * data->gm->ray.dir_y * d  * data->gm->dda.perp_dist), 1, 1, GREEN_PIXEL});
			d = d + 0.001;
		}
	}
}

void	plot_map(t_data *data)
{
	int	i;
	int	j;
	int	color;
	int	side;

	i = -1;
	side = 15;
	while(++i < data->gm->map->map_higth)
	{
		j = -1;
		while(++j < data->gm->map->map_width)
		{
			color = BLACK_PIXEL;
			if(data->gm->map->map[i][j] == '1')
				color = BRICK_PIXEL;
			if(data->gm->map->map[i][j] == '0' || data->gm->map->map[i][j] == 'N')
				color = BEIGE_PIXEL;
			render_rect(&data->img, (t_rect){j * side, i * side, side, side, color});
			render_rect(&data->img, (t_rect){data->gm->player.pos[0] * side, data->gm->player.pos[1]
				* side, 5, 5, RED_PIXEL});
			render_rect(&data->img, (t_rect){j * side, i * side, 1, side, BLUE_SKY_PIXEL});
			render_rect(&data->img, (t_rect){j * side, i * side, side, 1, BLUE_SKY_PIXEL});
		}
	}
	plot_rays(data);
}
