/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:22:05 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/11 16:35:10 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_img(t_texture_img **txt_img, void *mlx_ptr,
					t_map_header *txt_path)
{
	int	aux;

	(*txt_img)->ea->mlx_img = mlx_xpm_file_to_image(mlx_ptr,
			txt_path->ea, &aux, &aux);
	(*txt_img)->no->mlx_img = mlx_xpm_file_to_image(mlx_ptr,
			txt_path->no, &aux, &aux);
	(*txt_img)->we->mlx_img = mlx_xpm_file_to_image(mlx_ptr,
			txt_path->we, &aux, &aux);
	(*txt_img)->so->mlx_img = mlx_xpm_file_to_image(mlx_ptr,
			txt_path->so, &aux, &aux);
}

void	get_img_addr(t_texture_img **txt_img)
{
	(*txt_img)->ea->addr = mlx_get_data_addr((*txt_img)->ea->mlx_img,
			&(*txt_img)->ea->bpp, &(*txt_img)->ea->line_len,
			&(*txt_img)->ea->endian);
	(*txt_img)->no->addr = mlx_get_data_addr((*txt_img)->no->mlx_img,
			&(*txt_img)->no->bpp, &(*txt_img)->no->line_len,
			&(*txt_img)->no->endian);
	(*txt_img)->we->addr = mlx_get_data_addr((*txt_img)->we->mlx_img,
			&(*txt_img)->we->bpp, &(*txt_img)->we->line_len,
			&(*txt_img)->we->endian);
	(*txt_img)->so->addr = mlx_get_data_addr((*txt_img)->so->mlx_img,
			&(*txt_img)->so->bpp, &(*txt_img)->so->line_len,
			&(*txt_img)->so->endian);
}

void	check_img_is_valid(t_texture_img *texture, t_game **game)
{
	if (texture->ea->mlx_img == NULL || texture->no->mlx_img == NULL
		|| texture->we->mlx_img == NULL || texture->so->mlx_img == NULL)
		print_error_exit(game, "Invalid texture\n");
}

void	init_textures(t_game **game)
{
	create_img(&(*game)->texture_img, (*game)->mlx_data->mlx_ptr,
		(*game)->header);
	check_img_is_valid((*game)->texture_img, game);
	get_img_addr(&(*game)->texture_img);
}
