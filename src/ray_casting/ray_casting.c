/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:30:28 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/11 14:30:00 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	deg_to_rad(double degress)
{
	return (degress * (PI/180.0));
}

float	get_offset(t_game *game)
{
	float	offset = 0;
	int	cell_size = 64;

	if (game->ray->wall_plane == VERTICAL)
	{
		offset = (int)game->ray->y_coordinate % cell_size;
	}
	else if (game->ray->wall_plane == HORIZONTAL)
	{
		offset = (int)game->ray->x_coordinate % cell_size;
	}
	return (offset);
}

int	calc_color(t_img *img, double y1, float offset, double wall_height)
{
	unsigned int	color;
	double		texture_height;
	double		step;
	double		pixel;

	texture_height = 64;
	step = texture_height / wall_height;
	pixel = step * y1;
	color = *(unsigned int *) (img->addr + (int)pixel * img->line_len  + (int)offset * (img->bpp /8));
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
	int		i = 0;
	int		color;
	t_img	*txt_img;

	// txt_img = define_texture(game->ray->angle, game->texture_img, game->ray->wall_plane);
	// color = calc_color(txt_img, i, get_offset(game), wall_height);
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

void	put_texture(t_game *game)
{
	float	offset;

	offset = get_offset(game);

}

void	ray_casting(t_game *game)
{
	//double	d;
	// double	ray_length;
	// double	ray_angle;
	double	distance;
	double	correc_wall_distance;
	double	distance_to_proj_plane;
	double	wall_height;
	// int		ray_count;
	//t_ray_casting	*ray;

	game->ray->angle = game->player->angle - deg_to_rad(30);
	if (game->ray->angle < 0)
		game->ray->angle += 2*PI;
	game->ray->id = 0;
	while (game->ray->id < 900)
	{
		game->ray->length = 0;
		find_wall_distance(&game);
		distance_to_proj_plane = (900/2) / tan(deg_to_rad(60)/2);
		correc_wall_distance = game->ray->length * cos(game->ray->angle - game->player->angle);
		wall_height = (MAP_CELL / correc_wall_distance) * distance_to_proj_plane;
		draw_line(game->ray->id, (600/2)- (wall_height/2), (600/2)+ (wall_height/2), game, wall_height);
		//teste_texture(game);
		//put_texture(game);
		game->ray->angle += deg_to_rad(60)/900;
		game->ray->id++;
	}
}
