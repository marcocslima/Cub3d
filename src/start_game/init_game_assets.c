/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_assets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:14:22 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/16 11:28:15 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_window_img(t_img **img, void *mlx_ptr)
{
	init_data_img(img);
	(*img)->img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	(*img)->addr = mlx_get_data_addr((*img)->img_ptr, &(*img)->bpp,
			&(*img)->line_len, &(*img)->endian);
	(*img)->data = (int *)mlx_get_data_addr((*img)->img_ptr, &(*img)->bpp,
			&(*img)->line_len, &(*img)->endian);
}

void	init_game_assets(t_game **game)
{
	init_player(*game);
	init_data_mlx(&(*game)->mlx);
	init_window_img(&(*game)->img, (*game)->mlx->ptr);
	init_data_assets(&(*game)->texture_img, &(*game)->background_color, *game);
	init_textures(game);
}
