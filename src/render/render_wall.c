/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:19:12 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/13 14:20:01 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	get_x_offset(t_game *game)
{
	double	x_offset;

	x_offset = 0;
	if (game->ray->wall_plane == VERTICAL)
		x_offset = (int)game->ray->y_intersection % MAP_CELL;
	else if (game->ray->wall_plane == HORIZONTAL)
		x_offset = (int)game->ray->x_intersection % MAP_CELL;
	return (x_offset);
}

int	calc_color(t_img *img, double y, double x_offset, double wall_height)
{
	unsigned int	color;
	double			texture_height;
	double			step;
	double			y_offset;

	texture_height = MAP_CELL;
	step = texture_height / wall_height;
	y_offset = step * y;
	color = *(unsigned int *)(img->addr + (int)y_offset * img->line_len
			+ (int)x_offset * (img->bpp / 8));
	return (color);
}

void	render_textured_line(t_game *game, t_img *txtr_img, double y,
								double wall_height)
{
	int		i;
	double	x;

	i = 0;
	x = game->ray->id;
	while (i < wall_height)
	{
		render_line(game, calc_color(txtr_img, i,
				get_x_offset(game), wall_height), y, x);
		y++;
		i++;
	}
}

void	render_wall(double y, t_game *game, double wall_height)
{
	int		i;

	i = 0;
	if (game->ray->wall_plane == HORIZONTAL)
	{
		if (looking_up(game->ray->angle))
			render_textured_line(game, game->texture_img->no, y, wall_height);
		else
			render_textured_line(game, game->texture_img->so, y, wall_height);
	}
	else
	{
		if (looking_right(game->ray->angle))
			render_textured_line(game, game->texture_img->ea, y, wall_height);
		else
			render_textured_line(game, game->texture_img->we, y, wall_height);
	}
}
