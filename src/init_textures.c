/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:48:31 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/15 19:09:33 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_img(t_game **game)
{
	(*game)->tx_img[0].txt_img.img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->no, &(*game)->tx_img[0].txt_img.wdt,
			&(*game)->tx_img[0].txt_img.hgt);
	(*game)->tx_img[1].txt_img.img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->so, &(*game)->tx_img[1].txt_img.wdt,
			&(*game)->tx_img[1].txt_img.hgt);
	(*game)->tx_img[2].txt_img.img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->we, &(*game)->tx_img[2].txt_img.wdt,
			&(*game)->tx_img[2].txt_img.hgt);
	(*game)->tx_img[3].txt_img.img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->ea, &(*game)->tx_img[3].txt_img.wdt,
			&(*game)->tx_img[3].txt_img.hgt);
}

void	get_img_addr(t_game **game)
{
	(*game)->tx_img[1].txt_img.data = (int *)mlx_get_data_addr((*game)->tx_img[1]
			.txt_img.img_ptr, &(*game)->tx_img[1].txt_img.bpp, &(*game)->tx_img[1]
			.txt_img.line_len, &(*game)->tx_img[1].txt_img.endian);
	(*game)->tx_img[0].txt_img.data = (int *)mlx_get_data_addr((*game)->tx_img[0]
			.txt_img.img_ptr, &(*game)->tx_img[0].txt_img.bpp, &(*game)->tx_img[0]
			.txt_img.line_len, &(*game)->tx_img[0].txt_img.endian);
	(*game)->tx_img[2].txt_img.data = (int *)mlx_get_data_addr((*game)->tx_img[2]
			.txt_img.img_ptr, &(*game)->tx_img[2].txt_img.bpp, &(*game)->tx_img[2]
			.txt_img.line_len, &(*game)->tx_img[2].txt_img.endian);
	(*game)->tx_img[3].txt_img.data = (int *)mlx_get_data_addr((*game)->tx_img[3]
			.txt_img.img_ptr, &(*game)->tx_img[3].txt_img.bpp, &(*game)->tx_img[3]
			.txt_img.line_len, &(*game)->tx_img[3].txt_img.endian);
}

// void	check_img_is_valid(t_texture_img *texture, t_game **game)
// {
// 	if (texture->ea->mlx_img == NULL || texture->no->mlx_img == NULL
// 		|| texture->we->mlx_img == NULL || texture->so->mlx_img == NULL)
// 		print_error_exit(game, "Invalid texture\n");
// }

void	init_textures(t_game **game)
{
	create_img(game);
	//check_img_is_valid(game);
	get_img_addr(game);
}
