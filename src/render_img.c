/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:03:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/06 20:29:18 by alida-si         ###   ########.fr       */
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
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
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
		while (j < 900)
			img_pix_put(game->img_data, j++, i, COLOR_BLUE);
		++i;
	}

	i = 300;
	while (i < 600)
	{
		j = 0;
		while (j < 900)
			img_pix_put(game->img_data, j++, i, COLOR_GREEN);
		++i;
	}
}

int	render_rect(t_game *game, int color, int rect_height, int rect_width,
		int y_position, int x_position)
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
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < game->map->map_higth)
	{
		j = 0;
		while (j < game->map->map_width)
		{
			if (game->map->map[i][j] == '1')
				color = COLOR_WHITE;
			if (game->map->map[i][j] == '0' || game->map->map[i][j] == 'N')
				color = COLOR_BLACK;
			render_rect(game, color, MAP_CELL - 1, MAP_CELL - 1, i * MAP_CELL, j * MAP_CELL);
			j++;
		}
		i++;
	}
}

void	render_player(t_game *game)
{
	render_rect(game, COLOR_YELLOW, 1, 1, game->player->y_position,
			game->player->x_position);
}

void	teste(t_game *game)
{
	unsigned int		color;
	int		aux;
	int		i= 0;
	float		k,l = 0;
	float	step_ty = 0;
	int	j = 0;
	float	texture_height = 64;
	float	wall_height = 64;

	//  game->teste_img->mlx_img = mlx_xpm_file_to_image(game->mlx_data->mlx_ptr, "test.xpm", &aux, &aux);
	//  game->teste_img->addr = mlx_get_data_addr(game->teste_img->mlx_img, &game->teste_img->bpp, &game->teste_img->line_len, &game->teste_img->endian);

	step_ty = texture_height/wall_height;
	while (j < 64)
	{
		i = 0;
		l = 0;
		while (i < 64)
		{
			color = *(unsigned int *) (game->teste_img->addr + (int)k * game->teste_img->line_len  + (int)l * game->teste_img->bpp /8);
			img_pix_put (game->img_data, 450+i, 300+j, color);
			i++;
			l+=step_ty;
		}
		j++;
		k+=step_ty;
	}
}

int	render(t_game *game)
{
	render_background(game, COLOR_GRAY);
	//render_map(game);
	//render_player(game);
	ray_casting(game);
	teste(game);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win,
		game->img_data->mlx_img, 0, 0);
	return (1);
}
