/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:03:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/04 16:05:16 by alida-si         ###   ########.fr       */
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
	while (i < 500)
	{
		j = 0;
		while (j < 500)
			img_pix_put(game->img, j++, i, color);
		++i;
	}
}

int	render_rect(t_game *game)
{
	int	i;
	int	j;
	int	rect_height;
	int	rect_width;

	if (game->mlx_data->mlx_win == NULL)
		return (1);
	rect_height = 5;
	rect_width = 5;
	i = game->img->y_position;
	while (i < game->img->y_position + rect_height)
	{
		j = game->img->x_position;
		while (j < game->img->x_position + rect_width)
			img_pix_put(game->img, j++, i, COLOR_RED);
		++i;
	}
	return (0);
}

int	render(t_game *game)
{
	render_background(game, COLOR_BLACK);
	render_rect(game);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->img->mlx_img, 0, 0);
	return (1);
}
