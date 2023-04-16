/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:22:27 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/15 19:48:29 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	close_game(t_game **game)
{
	free_cub3d(game);
	exit(0);
}

int	end_game(t_game **game)
{
	mlx_destroy_image((*game)->mlx->ptr, (*game)->texture_img->no->img_ptr);
	mlx_destroy_image((*game)->mlx->ptr, (*game)->texture_img->so->img_ptr);
	mlx_destroy_image((*game)->mlx->ptr, (*game)->texture_img->we->img_ptr);
	mlx_destroy_image((*game)->mlx->ptr, (*game)->texture_img->ea->img_ptr);
	mlx_destroy_image((*game)->mlx->ptr, (*game)->img.img_ptr);
	mlx_destroy_window((*game)->mlx->ptr, (*game)->mlx->win);
	mlx_destroy_display((*game)->mlx->ptr);
	free((*game)->mlx->ptr);
	free(*game);
	close_game(game);
	exit(0);
	return (0);
}
