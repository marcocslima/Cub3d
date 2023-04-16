/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:48:31 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/16 14:02:08 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_txt_img(t_texture_img **img, t_map_header *header, void *mlx_ptr)
{
	int	a;

	a = 0;
	(*img)->no->img_ptr = mlx_xpm_file_to_image(mlx_ptr, header->no, &a, &a);
	(*img)->so->img_ptr = mlx_xpm_file_to_image(mlx_ptr, header->so, &a, &a);
	(*img)->we->img_ptr = mlx_xpm_file_to_image(mlx_ptr, header->we, &a, &a);
	(*img)->ea->img_ptr = mlx_xpm_file_to_image(mlx_ptr, header->ea, &a, &a);
}

void	get_img_addr(t_texture_img **img)
{
	(*img)->no->data = (int *)mlx_get_data_addr((*img)->no->img_ptr,
			&(*img)->no->bpp, &(*img)->no->line_len, &(*img)->no->endian);
	(*img)->so->data = (int *)mlx_get_data_addr((*img)->so->img_ptr,
			&(*img)->so->bpp, &(*img)->so->line_len, &(*img)->so->endian);
	(*img)->we->data = (int *)mlx_get_data_addr((*img)->we->img_ptr,
			&(*img)->we->bpp, &(*img)->we->line_len, &(*img)->we->endian);
	(*img)->ea->data = (int *)mlx_get_data_addr((*img)->ea->img_ptr,
			&(*img)->ea->bpp, &(*img)->ea->line_len, &(*img)->ea->endian);
}

void	check_img_is_valid(t_texture_img *texture, t_game **game)
{
	if (texture->ea->img_ptr == NULL || texture->no->img_ptr == NULL
		|| texture->we->img_ptr == NULL || texture->so->img_ptr == NULL)
		print_error_exit(game, "Invalid texture\n");
}

void	init_textures(t_game **game)
{
	create_txt_img(&(*game)->texture_img, (*game)->header, (*game)->mlx->ptr);
	check_img_is_valid((*game)->texture_img, game);
	get_img_addr(&(*game)->texture_img);
}
