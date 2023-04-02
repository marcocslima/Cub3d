/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:41:37 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/02 13:25:50 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_wall(t_data *data)
{
	data->gm->dda.wall_line_height = HEIGHT / data->gm->dda.perp_dist;
	data->gm->dda.line_start = HEIGHT / 2 - data->gm->dda.wall_line_height / 2;
	if (data->gm->dda.line_start < 0)
		data->gm->dda.line_start = 0;
	data->gm->dda.line_end = data->gm->dda.wall_line_height / 2 + HEIGHT / 2;
	if (data->gm->dda.line_end >= HEIGHT)
		data->gm->dda.line_end = HEIGHT - 1;
}

void	textures(float pixel, t_data *data)
{
	
}
