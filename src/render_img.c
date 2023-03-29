/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:03:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/29 11:04:45 by alida-si         ###   ########.fr       */
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

void	render_player(t_game *game)
{
	render_rect(game, COLOR_RED, 2, 2, game->player->y_position, game->player->x_position);
}

int	calculate_ray_length(t_game *game, int y_coordinate, int x_coordinate)
{
	int	delta_y;
	int	delta_x;

	delta_y = game->player->y_position - y_coordinate;
	delta_x = game->player->x_position - x_coordinate;
	return (sqrt(pow(delta_y, 2) + pow(delta_x, 2)));
}

int	hit_wall(t_game *game, int y_coordinate, int x_coordinate, int y_step, int x_step)
{
	int	cell_x;
	int	cell_y;

	cell_x = x_coordinate/40;
	cell_y = y_coordinate/40;
	while (cell_x >= 0 && cell_x < game->map->map_width && cell_y >= 0
	&& cell_y < game->map->map_higth && game->map->map[(y_coordinate/40)][x_coordinate/40] != '1')
	{
		y_coordinate += y_step;
		x_coordinate += x_step;
		cell_x = x_coordinate/40;
		cell_y = y_coordinate/40;
	}
	return (calculate_ray_length(game, y_coordinate, x_coordinate));
}

int	distance_to_horizontal_wall_up(t_game *game)
{
	int	y_coordinate;
	int	x_coordinate;
	int	x_step;
	int	y_step;
	int	ray_length;

	y_coordinate = ((int)game->player->y_position / 40) * 40 - 1;
	x_coordinate = ((int)(game->player->y_position - y_coordinate) / (-tan (game->player->angle))) + game->player->x_position;
	x_step = 40/-tan(game->player->angle);
	y_step = -40;
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}

int	distance_to_horizontal_wall_down(t_game *game)
{
	int	y_coordinate;
	int	x_coordinate;
	int	x_step;
	int	y_step;
	int	ray_length;

	y_coordinate = ((int)game->player->y_position / 40) * 40 + 40;
	x_coordinate = ((int)(game->player->y_position - y_coordinate) / (-tan (game->player->angle))) + game->player->x_position;
	x_step = 40/tan(game->player->angle);
	y_step = 40;
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}

int	distance_to_vertical_wall_right(t_game *game)
{
	int	y_coordinate;
	int	x_coordinate;
	int	x_step;
	int	y_step;
	int	ray_length;

	x_coordinate = ((int)game->player->x_position / 40) * 40 + 40;
	y_coordinate = (int)(game->player->x_position - x_coordinate) * ( -tan (game->player->angle)) + game->player->y_position;
	x_step = 40;
	y_step = 40 * tan(game->player->angle);
	ray_length = hit_wall(game, y_coordinate, x_coordinate, y_step, x_step);
	return (ray_length);
}

int	check_vertical_hit_wall_left(t_game *game)
{
	int	ay;
	int	ax;
	int	d_y;
	int	d_x;
	int	hipotenusa;

	//find first vertical intersection
	ax = game->player->x_position / 40;
	ax *= 40;
	ax -= 1;
	ay = (game->player->x_position - ax) * ( -tan (game->player->angle));
	ay += game->player->y_position;


	int x_step = -40;
	int y_step = 40 * -tan(game->player->angle);
	int bx= ax+x_step;
	int by= ay+y_step;

	d_y = game->player->y_position - ay;
	d_x = game->player->x_position - ax;
	hipotenusa = sqrt(pow(d_y, 2) + pow(d_x, 2));
	int cel_x = ax/40;
	int cel_y = ay/40;
	while (cel_x >= 0 && cel_x < game->map->map_width
			&& cel_y >= 0 && cel_y < game->map->map_higth && game->map->map[ay/40][ax/40] != '1')
	{
		ay += y_step;
		ax += x_step;
		d_y = game->player->y_position - ay;
		d_x = game->player->x_position - ax;
		hipotenusa = sqrt(pow(d_y, 2) + pow(d_x, 2));
		cel_x = ax/40;
		cel_y = ay/40;
	}
	return (hipotenusa);
}

int	looking_up(float angle)
{
	if (angle > PI && angle < 2 * PI)
		return (1);
	return (0);
}

int	looking_right(float angle)
{
	if (angle > 3*PI/2 || angle < PI/2)
		return (1);
	return (0);
}

int	shorter_distance(int x, int y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}

int	distance_to_horizontal_wall(t_game *game)
{
	if (looking_up(game->player->angle))
		return (distance_to_horizontal_wall_up(game));
	else
		return (distance_to_horizontal_wall_down(game));
}

int	distance_to_vertical_wall(t_game *game)
{
	if (looking_right(game->player->angle))
		return (distance_to_vertical_wall_right(game));
	else
		return (check_vertical_hit_wall_left(game));
}

int	find_wall_distance(t_game *game)
{
	int	vertical_wall_distance;
	int	horizontal_wall_distance;

	vertical_wall_distance = distance_to_vertical_wall(game);
	horizontal_wall_distance = distance_to_horizontal_wall(game);
	return (shorter_distance(horizontal_wall_distance, vertical_wall_distance));
}

void	ray_casting(t_game *game)
{
	float	d = 0.1;
	int		ray_length;

	ray_length = find_wall_distance(game);
	game->player->delta_x = cos(game->player->angle) * ray_length;
	game->player->delta_y = sin(game->player->angle) * ray_length;

	while(d < 1)
	{
		render_rect(game, COLOR_RED, 1, 1, game->player->y_position + game->player->delta_y * d, game->player->x_position + game->player->delta_x * d);
		d += 0.001;
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
