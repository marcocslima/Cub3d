/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:35:58 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/06 10:33:31 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	distance_to_horizontal_wall(t_game **game)
{
	if (looking_up((*game)->ray->angle))
		return (distance_to_horizontal_wall_up(game));
	else
		return (distance_to_horizontal_wall_down(game));
}

double	distance_to_vertical_wall(t_game **game)
{
	if (looking_right((*game)->ray->angle))
		return (distance_to_vertical_wall_right(game));
	else
		return (distance_to_vertical_wall_left(game));
}

void	define_wall_color(t_game **game, int color)
{
	(*game)->ray->wall_color = color;
}

void	find_wall_distance(t_game **game)
{
	double	vertical_wall_distance;
	double	horizontal_wall_distance;

	vertical_wall_distance = distance_to_vertical_wall(game);
	horizontal_wall_distance = distance_to_horizontal_wall(game);
	if (vertical_wall_distance < horizontal_wall_distance)
	{
		(*game)->ray->wall_plane = VERTICAL;
		(*game)->ray->wall_color = COLOR_LIGHT_PINK;
	}
	else if (vertical_wall_distance > horizontal_wall_distance)
	{
		(*game)->ray->wall_plane = HORIZONTAL;
		(*game)->ray->wall_color = COLOR_PINK;
	}
}
