/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:35:58 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/30 13:32:44 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	distance_to_horizontal_wall(t_game *game, float angle)
{
	if (looking_up(game->player->angle))
		return (distance_to_horizontal_wall_up(game, angle));
	else
		return (distance_to_horizontal_wall_down(game, angle));
}

float	distance_to_vertical_wall(t_game *game, float angle)
{
	if (looking_right(game->player->angle))
		return (distance_to_vertical_wall_right(game, angle));
	else
		return (distance_to_vertical_wall_left(game, angle));
}

float	find_wall_distance(t_game *game, float angle)
{
	int	vertical_wall_distance;
	int	horizontal_wall_distance;

	vertical_wall_distance = distance_to_vertical_wall(game, angle);
	horizontal_wall_distance = distance_to_horizontal_wall(game, angle);
	return (shorter_distance(horizontal_wall_distance, vertical_wall_distance));
}
