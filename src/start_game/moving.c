/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/07 08:14:58 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	moving_up(float	desloc, t_data *data)
{
	int		tmp_0;
	int		tmp_1;

	tmp_0 = (int)(data->gm->player.pos[0] + data->gm->player.dir[0] * 0.5);
	tmp_1 = (int)(data->gm->player.pos[1] + data->gm->player.dir[1] * 0.5);
	if(data->gm->map->map[tmp_1][tmp_0] != '1')
	{
		data->gm->player.pos[0] += data->gm->player.dir[0] * desloc;
		data->gm->player.pos[1] += data->gm->player.dir[1] * desloc;
	}
}

void	moving_down(float	desloc, t_data *data)
{
	int		tmp_0;
	int		tmp_1;

	tmp_0 = (int)(data->gm->player.pos[0] - data->gm->player.dir[0] * 0.5);
	tmp_1 = (int)(data->gm->player.pos[1] - data->gm->player.dir[1] * 0.5);
	if(data->gm->map->map[tmp_1][tmp_0] != '1')
	{
		data->gm->player.pos[0] -= data->gm->player.dir[0] * desloc;
		data->gm->player.pos[1] -= data->gm->player.dir[1] * desloc;
	}
}

void	moving_left(float	desloc, t_data *data)
{
	int		tmp_0;
	int		tmp_1;

	tmp_0 = (int)(data->gm->player.pos[0] + data->gm->player.dir[1] * 0.5);
	tmp_1 = (int)(data->gm->player.pos[1] - data->gm->player.dir[0] * 0.5);
	if(data->gm->map->map[tmp_1][tmp_0] != '1')
	{
		data->gm->player.pos[0] += data->gm->player.dir[1] * desloc;
		data->gm->player.pos[1] -= data->gm->player.dir[0] * desloc;
	}
}

void	moving_right(float	desloc, t_data *data)
{
	int		tmp_0;
	int		tmp_1;

	tmp_0 = (int)(data->gm->player.pos[0] - data->gm->player.dir[1] * 0.5);
	tmp_1 = (int)(data->gm->player.pos[1] + data->gm->player.dir[0] * 0.5);
	if(data->gm->map->map[tmp_1][tmp_0] != '1')
	{
		data->gm->player.pos[0] -= data->gm->player.dir[1] * desloc;
		data->gm->player.pos[1] += data->gm->player.dir[0] * desloc;
	}
}

int moving(int key, t_data *data)
{
	int		tmp_0;
	int		tmp_1;
	float	desloc;

	desloc = 0.1;
	if (key == A)
		moving_left(desloc, data);
	if (key == D)
		moving_right(desloc, data);
	if (key == W)
		moving_up(desloc, data);
	if (key == S)
		moving_down(desloc, data);
	if (key == 65361)
		looking(- PI / 100, data);
	if (key == 65363)
		looking(+ PI / 100, data);
	return(0);
}
