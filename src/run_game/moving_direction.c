/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/22 00:12:47 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	moving_direction(float ang, t_game **game)
{
	float	tmp;
	float	tmp_plane;

	tmp = cos(ang) * (*game)->player.dir_x - sin(ang) * (*game)->player.dir_y;
	(*game)->player.dir_y = sin(ang) * (*game)->player.dir_x + cos(ang)
		* (*game)->player.dir_y;
	(*game)->player.dir_x = tmp;
	tmp_plane = cos(ang) * (*game)->player.cam_plane_x
		- sin(ang) * (*game)->player.cam_plane_y;
	(*game)->player.cam_plane_y = sin(ang) * (*game)->player.cam_plane_x
		+ cos(ang) * (*game)->player.cam_plane_y;
	(*game)->player.cam_plane_x = tmp_plane;
	return (0);
}
