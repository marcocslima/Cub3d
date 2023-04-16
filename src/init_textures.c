/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:48:31 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/16 09:09:09 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_img(t_game **game)
{
	int	aux;

	aux = 0;
	(*game)->texture_img->no->img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->no, &aux, &aux);
	(*game)->texture_img->so->img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->so, &aux, &aux);
	(*game)->texture_img->we->img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->we, &aux, &aux);
	(*game)->texture_img->ea->img_ptr = mlx_xpm_file_to_image((*game)->mlx->ptr,
			(*game)->header->ea, &aux, &aux);
}

void	get_img_addr(t_game **game)
{
	(*game)->texture_img->no->data = (int *)mlx_get_data_addr((*game)->texture_img->no->img_ptr,
	 &(*game)->texture_img->no->bpp, &(*game)->texture_img->no->line_len, &(*game)->texture_img->no->endian);
	(*game)->texture_img->so->data = (int *)mlx_get_data_addr((*game)->texture_img->so->img_ptr,
	 &(*game)->texture_img->so->bpp, &(*game)->texture_img->so->line_len, &(*game)->texture_img->so->endian);
	(*game)->texture_img->we->data = (int *)mlx_get_data_addr((*game)->texture_img->we->img_ptr,
	 &(*game)->texture_img->we->bpp, &(*game)->texture_img->we->line_len, &(*game)->texture_img->we->endian);
	(*game)->texture_img->ea->data = (int *)mlx_get_data_addr((*game)->texture_img->ea->img_ptr,
	 &(*game)->texture_img->ea->bpp, &(*game)->texture_img->ea->line_len, &(*game)->texture_img->ea->endian);
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
