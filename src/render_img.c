/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:03:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/29 11:44:04 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_game *game, int color)
{
	int	i;
	int	j;

	if (game->mlx_data->mlx_win == NULL)
		return ;
	i = 0;
	while (i < 600)
	{
		j = 0;
		while (j < 1500)
			img_pix_put(game->img_data, j++, i, color);
		++i;
	}
}

int	render_rect(t_game *game, int color, int rect_height, int rect_width, int y_position, int x_position)
{
	int	i;
	int	j;

	if (game->mlx_data->mlx_win == NULL)
		return (1);
	i = y_position;
	while (i < y_position + rect_height)
	{
		j = x_position;
		while (j < x_position + rect_width)
			img_pix_put(game->img_data, j++, i, color);
		++i;
	}
	return (0);
}

void	render_map(t_game *game)
{
	int i = 0;
	int j = 0;
	int	color;

	while (i < game->map->map_higth)
	{
		j = 0;
		while (j < game->map->map_width)
		{
			if (game->map->map[i][j] == '1')
				color = COLOR_WHITE;
			if (game->map->map[i][j] == '0' || game->map->map[i][j] == 'N')
				color = COLOR_BLACK;
			render_rect(game, color, 39, 39, i*40, j*40);
			j++;
		}
		i++;
	}
}

int	render(t_game *game)
{
	render_background(game, COLOR_GRAY);
	render_map(game);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->img_data->mlx_img, 0, 0);
	return (1);
}
