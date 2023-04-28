/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/28 07:07:11 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	moving_up(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos_x + (*game)->player.dir_x * 0.5);
	tmp_1 = (int)((*game)->player.pos_y + (*game)->player.dir_y * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos_x += (*game)->player.dir_x * desloc;
		(*game)->player.pos_y += (*game)->player.dir_y * desloc;
	}
}

void	moving_down(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos_x - (*game)->player.dir_x * 0.5);
	tmp_1 = (int)((*game)->player.pos_y - (*game)->player.dir_y * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos_x -= (*game)->player.dir_x * desloc;
		(*game)->player.pos_y -= (*game)->player.dir_y * desloc;
	}
}

void	moving_left(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos_x + (*game)->player.dir_y * 0.5);
	tmp_1 = (int)((*game)->player.pos_y - (*game)->player.dir_x * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos_x += (*game)->player.dir_y * desloc;
		(*game)->player.pos_y -= (*game)->player.dir_x * desloc;
	}
}

void	moving_right(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos_x - (*game)->player.dir_y * 0.5);
	tmp_1 = (int)((*game)->player.pos_y + (*game)->player.dir_x * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos_x -= (*game)->player.dir_y * desloc;
		(*game)->player.pos_y += (*game)->player.dir_x * desloc;
	}
}

int	moving(int key, t_game *game)
{
	float	desloc;

	desloc = 0.1;
	if (key == A)
		moving_left(desloc, &game);
	if (key == D)
		moving_right(desloc, &game);
	if (key == W)
		moving_up(desloc, &game);
	if (key == S)
		moving_down(desloc, &game);
	if (key == LEFT_ARROW)
		moving_direction(-PI / 100, &game);
	if (key == RIGHT_ARROW)
		moving_direction(+PI / 100, &game);
	if (key == KEY_ESC)
		end_game(&game);
	return (0);
}
