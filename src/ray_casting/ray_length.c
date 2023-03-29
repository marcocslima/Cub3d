/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:35:58 by alida-si          #+#    #+#             */
/*   Updated: 2023/03/29 13:39:32 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		return (distance_to_vertical_wall_left(game));
}

int	find_wall_distance(t_game *game)
{
	int	vertical_wall_distance;
	int	horizontal_wall_distance;

	vertical_wall_distance = distance_to_vertical_wall(game);
	horizontal_wall_distance = distance_to_horizontal_wall(game);
	return (shorter_distance(horizontal_wall_distance, vertical_wall_distance));
}
