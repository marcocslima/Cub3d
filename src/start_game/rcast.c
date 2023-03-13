/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:01:30 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/13 09:13:28 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	drawRay(t_data *data)
{
	int r,mx,my,mp,dof;
	float rx,ry,ra,xo,yo;
	ra = data->gm->ang;
	for (r = 0; r < 1; r++)
	{
		dof = 0;
		float aTan = -1 / tan(ra);
		if(ra<PI)
		{
			ry = (((int) data->gm->player.pos[1] >> 6) << 6) - 0.0001;
			rx = (data->gm->player.pos[1] - ry) * aTan + data->gm->player.pos[0];
			yo = -64;
			xo = -yo * aTan;
		}
		if(ra>PI)
		{
			ry = (((int) data->gm->player.pos[1] >> 6)<<6) + 64;
			rx = (data->gm->player.pos[1] - ry) * aTan + data->gm->player.pos[0];
			yo = 64;
			xo = -yo * aTan;
		}
		if(ra==0 || ra==PI)
		{
			rx = data->gm->player.pos[0];
			ry = data->gm->player.pos[1];
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * data->gm->map->map_higth + mx;
			if(mp < data->gm->map->map_higth * data->gm->map->map_width) //&& data->gm->map->map[mp] == 1)
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
	}
		printf("##################################################################\n");
		
		printf("ra: %f\n", ra);
		printf("\nr: %d - mx: %d - my: %d - mp: %d - dof: %d\n", r,mx,my,mp,dof);
		printf("\nrx: %f - ry: %f - ra: %f - xo: %f - yo: %f - mp: %d\n", rx,ry,ra,xo,yo, mp);
		// printf("ang: %d\n",data->gm->ang);
	return(0);
}

void	ray_dir(float pixel, t_data *data)
{
	float	multiplier;
	float	camera_pixel[2];

	multiplier = 2 * (pixel / WIDTH) - 1;
	camera_pixel[0] = data->gm->player.cam_plane[0] * multiplier;
	camera_pixel[1] = data->gm->player.cam_plane[1] * multiplier;
	data->gm->ray.dir_x = data->gm->player.dir[0] + camera_pixel[0];
	data->gm->ray.dir_y = data->gm->player.dir[1] + camera_pixel[1];
	float tmp;
	if (tmp != data->gm->ang)
	{
		tmp = data->gm->ang;
		printf("x: %f\n", data->gm->ray.dir_x);
		printf("y: %f\n", data->gm->ray.dir_y);
		printf("player_x: %f\n", data->gm->player.pos[0]);
		printf("player_y: %f\n", data->gm->player.pos[1]);
		printf("ang: %f\n", data->gm->ang);
		printf("sin: %f\n", sin(data->gm->ang));
		printf("cos: %f\n", cos(data->gm->ang));
		printf("tan: %f\n", tan(data->gm->ang));
		printf("aTan: %f\n", atan(data->gm->ang));
		float ad = data->gm->player.pos[0] - (int)data->gm->player.pos[0];
		float op = tan(data->gm->ang) * (data->gm->player.pos[0] - (int)data->gm->player.pos[0]);
		printf("cateto Adj: %f\n", ad);
		printf("cateto Op: %f\n", op);
		printf("hipotenusa: %f\n", sqrt(pow(ad,2)+pow(op,2)));
	}
}