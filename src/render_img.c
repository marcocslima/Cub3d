/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:03:17 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/26 18:07:27 by alida-si         ###   ########.fr       */
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

double rad_to_deg(double radians) {
    return radians * (180.0 / PI);
}

int	check_hit_wall_up(t_game *game)
{
	int	ay;
	int	ax;
	int	d_y;
	int	d_x;
	int	hipotenusa;

	if (game->player->angle == 0)
		return (60);
	ay = game->player->y_position / 40;
	ay *= 40;
	ax = (game->player->y_position - ay) / (-tan (game->player->angle));
	ax += game->player->x_position;
	d_y = game->player->y_position - ay;
	d_x = game->player->x_position - ax;
	int x_step = 40/-tan(game->player->angle);
	int y_step = -40;
	int bx= ax+x_step;
	int by= ay+y_step;
	d_y = game->player->y_position - ay;
	d_x = game->player->x_position - ax;
	hipotenusa = sqrt(pow(d_y, 2) + pow(d_x, 2));
	int cel_x = ax/40;
	int cel_y = ay/40 - 1;
	while (cel_x >= 0 && cel_x < game->map->map_width
			&& cel_y >= 0 && cel_y < game->map->map_higth && game->map->map[(ay/40) - 1][ax/40] != '1')
	{
		ay -= 40;
		ax += x_step;
		d_y = game->player->y_position - ay;
		d_x = game->player->x_position - ax;
		hipotenusa = sqrt(pow(d_y, 2) + pow(d_x, 2));
		cel_x = ax/40;
		cel_y = ay/40 - 1;
	}
	return (hipotenusa);
}

int	check_hit_wall_down(t_game *game)
{
	int	ay;
	int	ax;
	int	d_y;
	int	d_x;
	int	hipotenusa;

	if (game->player->angle == 0)
		return (60);
	ay = game->player->y_position / 40;
	ay *= 40;
	ay += 40;
	ax = (game->player->y_position - ay) / (-tan (game->player->angle));
	ax += game->player->x_position;
	d_y = game->player->y_position - ay;
	d_x = game->player->x_position - ax;
	int x_step = 40/tan(game->player->angle);
	int y_step = 40;
	int bx= ax+x_step;
	int by= ay+y_step;
	d_y = game->player->y_position - ay;
	d_x = game->player->x_position - ax;
	hipotenusa = sqrt(pow(d_y, 2) + pow(d_x, 2));
	int cel_x = ax/40;
	int cel_y = ay/40;
	while (cel_x >= 0 && cel_x < game->map->map_width
			&& cel_y >= 0 && cel_y < game->map->map_higth && game->map->map[(ay/40)][ax/40] != '1')
	{
		ay += 40;
		ax += x_step;
		d_y = game->player->y_position - ay;
		d_x = game->player->x_position - ax;
		hipotenusa = sqrt(pow(d_y, 2) + pow(d_x, 2));
		cel_x = ax/40;
		cel_y = ay/40;
	}
	return (hipotenusa);
}

int	check_vertical_hit_wall_rigth(t_game *game)
{
	int	ay;
	int	ax;
	int	d_y;
	int	d_x;
	int	hipotenusa;

	if (game->player->angle == 0)
		return (60);
	ax = game->player->x_position / 40;
	ax *= 40;
	ax += 40;
	ay = (game->player->x_position - ax) * ( -tan (game->player->angle));
	ay += game->player->y_position;


	int x_step = 40;
	int y_step = 40 * tan(game->player->angle);
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

int	check_vertical_hit_wall_left(t_game *game)
{
	int	ay;
	int	ax;
	int	d_y;
	int	d_x;
	int	hipotenusa;

	if (game->player->angle == 0)
		return (60);
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

int	check_hit_wall(t_game *game)
{
	int vertical;
	int horizontal;

	if (game->player->angle > PI && game->player->angle < 2 * PI)
	{
		horizontal = (check_hit_wall_up(game));
		if (game->player->angle > 3*PI/2 || game->player->angle < PI/2)
			vertical = check_vertical_hit_wall_rigth(game);
		if (game->player->angle < 3*PI/2 && game->player->angle > PI/2)
		{
			vertical = check_vertical_hit_wall_left(game);
		}
	}
	else
	{
		horizontal = (check_hit_wall_down(game));
		if (game->player->angle >= 3*PI/2 || game->player->angle <= PI/2)
			vertical = check_vertical_hit_wall_rigth(game);
		else
			vertical = check_vertical_hit_wall_left(game);
	}
	if (horizontal < vertical)
		return (horizontal);
	else
		return (vertical);
	return(-1);
}

void	teste(t_game *game)
{
	float d = 0.1;
	game->player->delta_x = cos(game->player->angle) * check_hit_wall(game);
	game->player->delta_y = sin(game->player->angle) * check_hit_wall(game);

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
	//render_player(game);
	teste(game);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win, game->img_data->mlx_img, 0, 0);
	return (1);
}
