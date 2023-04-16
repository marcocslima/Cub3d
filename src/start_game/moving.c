/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/16 13:50:17 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	moving_up(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos[0] + (*game)->player.dir[0] * 0.5);
	tmp_1 = (int)((*game)->player.pos[1] + (*game)->player.dir[1] * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos[0] += (*game)->player.dir[0] * desloc;
		(*game)->player.pos[1] += (*game)->player.dir[1] * desloc;
	}
}

void	moving_down(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos[0] - (*game)->player.dir[0] * 0.5);
	tmp_1 = (int)((*game)->player.pos[1] - (*game)->player.dir[1] * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos[0] -= (*game)->player.dir[0] * desloc;
		(*game)->player.pos[1] -= (*game)->player.dir[1] * desloc;
	}
}

void	moving_left(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos[0] + (*game)->player.dir[1] * 0.5);
	tmp_1 = (int)((*game)->player.pos[1] - (*game)->player.dir[0] * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos[0] += (*game)->player.dir[1] * desloc;
		(*game)->player.pos[1] -= (*game)->player.dir[0] * desloc;
	}
}

void	moving_right(float desloc, t_game **game)
{
	int	tmp_0;
	int	tmp_1;

	tmp_0 = (int)((*game)->player.pos[0] - (*game)->player.dir[1] * 0.5);
	tmp_1 = (int)((*game)->player.pos[1] + (*game)->player.dir[0] * 0.5);
	if ((*game)->map->matrix[tmp_1][tmp_0] != '1')
	{
		(*game)->player.pos[0] -= (*game)->player.dir[1] * desloc;
		(*game)->player.pos[1] += (*game)->player.dir[0] * desloc;
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
	if (key == 65361)
		looking(-PI / 100, &game);
	if (key == 65363)
		looking(+PI / 100, &game);
	if (key == KEY_ESC)
		end_game(&game);
	return (0);
}
