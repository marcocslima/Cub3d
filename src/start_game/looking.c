/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/09 15:40:21 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	looking(float ang, t_data *data)
{
	float	tmp;
	float	tmp_plane;

	tmp = cos(ang) * data->gm->player.dir[0] - sin(ang)
		* data->gm->player.dir[1];
	data->gm->player.dir[1] = sin(ang) * data->gm->player.dir[0] + cos(ang)
		* data->gm->player.dir[1];
	data->gm->player.dir[0] = tmp;
	tmp_plane = cos(ang) * data->gm->player.cam_plane[0]
		- sin(ang) * data->gm->player.cam_plane[1];
	data->gm->player.cam_plane[1] = sin(ang) * data->gm->player.cam_plane[0]
		+ cos(ang) * data->gm->player.cam_plane[1];
	data->gm->player.cam_plane[0] = tmp_plane;
	return (0);
}
