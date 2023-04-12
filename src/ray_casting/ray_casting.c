/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/12 15:53:46 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	deg_to_rad(double degress)
{
	return (degress * (PI / 180.0));
}

double	get_offset(t_game *game)
{
	double	offset;

	offset = 0;
	if (game->ray->wall_plane == VERTICAL)
		offset = (int)game->ray->y_coordinate % MAP_CELL;
	else if (game->ray->wall_plane == HORIZONTAL)
		offset = (int)game->ray->x_coordinate % MAP_CELL;
	return (offset);
}

int	calc_color(t_img *img, double y1, double offset, double wall_height)
{
	unsigned int	color;
	double			texture_height;
	double			step;
	double			pixel;

	texture_height = MAP_CELL;
	step = texture_height / wall_height;
	pixel = step * y1;
	color = *(unsigned int *) (img->addr + (int)pixel * img->line_len + (int)offset * (img->bpp / 8));
	return (color);
}

t_img	*define_texture(double ray_angle, t_texture_img *txt_img, int wall_plane)
{
	if (wall_plane == HORIZONTAL)
	{
		if (looking_up(ray_angle))
			return (txt_img->no);
		else
			return (txt_img->so);
	}
	else
	{
		if (looking_right(ray_angle))
			return (txt_img->ea);
		else
			return (txt_img->we);
	}
}

void	draw_line(double x1, double y1, double y2, t_game *game, double wall_height)
{
	int		i;
	int		color;
	t_img	*txt_img;

	i = 0;
	if (game->ray->wall_plane == HORIZONTAL)
	{
		while (i < wall_height)
		{
			if (looking_up(game->ray->angle))
				render_rect(game, calc_color(game->texture_img->no, i, get_offset(game), wall_height), 1, 1, y1, x1);
			else
				render_rect(game, calc_color(game->texture_img->so, i, get_offset(game), wall_height), 1, 1, y1, x1);
			y1++;
			i++;
		}
	}
	else
	{
		while (i < wall_height)
		{
			if (looking_right(game->ray->angle))
				render_rect(game, calc_color(game->texture_img->ea, i, get_offset(game), wall_height), 1, 1, y1, x1);
			else
				render_rect(game, calc_color(game->texture_img->we, i, get_offset(game), wall_height), 1, 1, y1, x1);
			y1++;
			i++;
		}
	}
}

double	calculate_wall_height(t_game *game)
{
	double	correc_wall_distance;
	double	distance_to_proj_plane;
	double	wall_height;

	distance_to_proj_plane = (WINDOW_WIDTH / 2) / tan(deg_to_rad(FOV_ANGLE) / 2);
	correc_wall_distance = game->ray->length * cos(game->ray->angle - game->player->angle);
	wall_height = (MAP_CELL / correc_wall_distance) * distance_to_proj_plane;
	return (wall_height);
}

void	ray_casting(t_game *game)
{
	double	wall_height;

	game->ray->angle = game->player->angle - deg_to_rad(FOV_ANGLE / 2);
	if (game->ray->angle < 0)
		game->ray->angle += 2 * PI;
	game->ray->id = 0;
	while (game->ray->id < WINDOW_WIDTH)
	{
		game->ray->length = 0;
		find_wall_distance(&game);
		wall_height = calculate_wall_height(game);
		draw_line(game->ray->id, (WINDOW_HEIGHT / 2)- (wall_height / 2), (WINDOW_HEIGHT / 2) + (wall_height / 2), game, wall_height);
		game->ray->angle += deg_to_rad(FOV_ANGLE) / WINDOW_WIDTH;
		game->ray->id++;
	}
}
