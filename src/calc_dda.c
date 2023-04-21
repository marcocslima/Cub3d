/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:55:32 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/21 16:56:35 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(t_game *game)
{
	if (game->map->matrix[game->dda.map_pos_y][game->dda.map_pos_x] == '1')
		return (1);
	return (0);
}

void	increment_line_size_x(t_game **game)
{
	(*game)->dda.map_pos_x += (*game)->dda.map_step_x;
	(*game)->dda.line_size_x += (*game)->dda.offset_x;
	(*game)->dda.hit_side = VERTICAL;
}

void	increment_line_size_y(t_game **game)
{
	(*game)->dda.map_pos_y += (*game)->dda.map_step_y;
	(*game)->dda.line_size_y += (*game)->dda.offset_y;
	(*game)->dda.hit_side = HORIZONTAL;
}

void	calc_dda(t_game **game)
{
	(*game)->dda.line_size_x = (*game)->dda.first_offset_x;
	(*game)->dda.line_size_y = (*game)->dda.first_offset_y;
	while (hit_wall(*game) == FALSE)
	{
		if ((*game)->dda.line_size_x < (*game)->dda.line_size_y)
			increment_line_size_x(game);
		else
			increment_line_size_y(game);
	}
}
