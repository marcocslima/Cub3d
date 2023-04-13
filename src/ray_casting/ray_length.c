/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:35:58 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/13 12:10:32 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	distance_to_horizontal_wall(t_game **game)
{
	if (looking_up((*game)->ray->angle))
		distance_to_horizontal_wall_up(game);
	else
		distance_to_horizontal_wall_down(game);
}

void	distance_to_vertical_wall(t_game **game)
{
	if (looking_right((*game)->ray->angle))
		distance_to_vertical_wall_right(game);
	else
		distance_to_vertical_wall_left(game);
}

void	find_wall_distance(t_game **game)
{
	distance_to_vertical_wall(game);
	distance_to_horizontal_wall(game);
}
