/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:01:30 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/19 10:04:23 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_dir(float pixel, t_data *data)
{
	float	multip;
	float	cam_pixel[2];

	multip = 2 * (pixel / WIDTH) - 1;
	cam_pixel[0] = data->gm->player.cam_plane[0] * multip;
	cam_pixel[1] = data->gm->player.cam_plane[1] * multip;
	data->gm->ray.dir_x = data->gm->player.dir[0] + cam_pixel[0];
	data->gm->ray.dir_y = data->gm->player.dir[1] + cam_pixel[1];
}

void	calc_delta_dist(t_data *data)
{
	data->gm->dists.delta_dist_x = fabs(sqrt(pow(data->gm->ray.dir_x,2) + pow(data->gm->ray.dir_y,2)) / data->gm->ray.dir_x);
	data->gm->dists.delta_dist_y = fabs(sqrt(pow(data->gm->ray.dir_x,2) + pow(data->gm->ray.dir_y,2)) / data->gm->ray.dir_y);

	printf("%f - %f\n",data->gm->dists.delta_dist_x,data->gm->dists.delta_dist_y);
}