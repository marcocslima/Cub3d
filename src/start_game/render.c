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

void	load_textures(t_data *data)
{
	data->gm->tx_img[0].txt_img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->gm->header->no[1], &data->gm->tx_img[0].txt_img.wdt, &data->gm->tx_img[0].txt_img.hgt);
	if (!data->gm->tx_img[0].txt_img.mlx_img)
		printf("procedimento de erro aqui!!!!");
	data->gm->tx_img[0].txt_img.data = (int *)mlx_get_data_addr(data->gm->tx_img[0].txt_img.mlx_img,
		&data->gm->tx_img[0].txt_img.bpp, &data->gm->tx_img[0].txt_img.line_len, &data->gm->tx_img[0].txt_img.endian);
	data->gm->tx_img[1].txt_img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->gm->header->so[1], &data->gm->tx_img[1].txt_img.wdt, &data->gm->tx_img[1].txt_img.hgt);
	if (!data->gm->tx_img[1].txt_img.mlx_img)
		printf("procedimento de erro aqui!!!!");
	data->gm->tx_img[1].txt_img.data = (int *)mlx_get_data_addr(data->gm->tx_img[1].txt_img.mlx_img,
		&data->gm->tx_img[1].txt_img.bpp, &data->gm->tx_img[1].txt_img.line_len, &data->gm->tx_img[1].txt_img.endian);
	data->gm->tx_img[2].txt_img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->gm->header->we[1], &data->gm->tx_img[2].txt_img.wdt, &data->gm->tx_img[2].txt_img.hgt);
	if (!data->gm->tx_img[2].txt_img.mlx_img)
		printf("procedimento de erro aqui!!!!");
	data->gm->tx_img[2].txt_img.data = (int *)mlx_get_data_addr(data->gm->tx_img[2].txt_img.mlx_img,
		&data->gm->tx_img[2].txt_img.bpp, &data->gm->tx_img[2].txt_img.line_len, &data->gm->tx_img[2].txt_img.endian);
	data->gm->tx_img[3].txt_img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->gm->header->ea[1], &data->gm->tx_img[3].txt_img.wdt, &data->gm->tx_img[3].txt_img.hgt);
	if (!data->gm->tx_img[3].txt_img.mlx_img)
		printf("procedimento de erro aqui!!!!");
	data->gm->tx_img[3].txt_img.data = (int *)mlx_get_data_addr(data->gm->tx_img[3].txt_img.mlx_img,
		&data->gm->tx_img[3].txt_img.bpp, &data->gm->tx_img[3].txt_img.line_len, &data->gm->tx_img[3].txt_img.endian);
}

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
