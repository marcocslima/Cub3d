/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_assets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:14:22 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 15:35:54 by alida-si         ###   ########.fr       */
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

void	init_data_assets(t_texture_img **texture_img,
						t_color **background_color, t_game *game)
{
	*texture_img = (t_texture_img *) malloc(sizeof(t_texture_img));
	*background_color = (t_color *) malloc(sizeof(t_color));
	init_data_img(&(*texture_img)->ea);
	init_data_img(&(*texture_img)->no);
	init_data_img(&(*texture_img)->so);
	init_data_img(&(*texture_img)->we);
	get_background_rgb(game);
}

void	init_player(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.cam_plane_x = 0.66;
	game->player.cam_plane_y = 0;
	get_player_position(game);
}

void	init_game_assets(t_game **game)
{
	init_player(*game);
	init_data_mlx(&(*game)->mlx);
	init_window_img(&(*game)->img, (*game)->mlx->ptr);
	init_data_assets(&(*game)->texture_img, &(*game)->background_color, *game);
	init_textures(game);
}
