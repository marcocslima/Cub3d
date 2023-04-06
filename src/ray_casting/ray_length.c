/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:35:58 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/06 09:12:38 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	distance_to_horizontal_wall(t_game *game, double angle)
{
	if (looking_up(angle))
		return (distance_to_horizontal_wall_up(game, angle));
	else
		return (distance_to_horizontal_wall_down(game, angle));
}

double	distance_to_vertical_wall(t_game *game, double angle)
{
	if (looking_right(angle))
		return (distance_to_vertical_wall_right(game, angle));
	else
		return (distance_to_vertical_wall_left(game, angle));
}

void	define_wall_color(t_game **game, int color)
{
	(*game)->ray->wall_color = color;
}

double	find_wall_distance(t_game *game, double angle)
{
	double	vertical_wall_distance;
	double	horizontal_wall_distance;

	vertical_wall_distance = distance_to_vertical_wall(game, angle);
	horizontal_wall_distance = distance_to_horizontal_wall(game, angle);
	if (vertical_wall_distance < horizontal_wall_distance)
	{
		(&*game)->ray->wall_plane = VERTICAL;
		define_wall_color(&game, COLOR_LIGHT_PINK);
	}
	else if (vertical_wall_distance > horizontal_wall_distance)
	{
		(&*game)->ray->wall_plane = HORIZONTAL;
		define_wall_color(&game, COLOR_PINK);
	}
	return (shorter_distance(horizontal_wall_distance, vertical_wall_distance));
}
