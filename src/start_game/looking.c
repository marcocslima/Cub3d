/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/17 15:52:05 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	looking(float ang, t_game **game)
{
	float	tmp;
	float	tmp_plane;

	tmp = cos(ang) * (*game)->player.dir_x - sin(ang)
		* (*game)->player.dir_y;
	(*game)->player.dir_y = sin(ang) * (*game)->player.dir_x + cos(ang)
		* (*game)->player.dir_y;
	(*game)->player.dir_x = tmp;
	tmp_plane = cos(ang) * (*game)->player.cam_plane[0]
		- sin(ang) * (*game)->player.cam_plane[1];
	(*game)->player.cam_plane[1] = sin(ang) * (*game)->player.cam_plane[0]
		+ cos(ang) * (*game)->player.cam_plane[1];
	(*game)->player.cam_plane[0] = tmp_plane;
	return (0);
}
