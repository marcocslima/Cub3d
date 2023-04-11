/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:22:27 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/10 21:10:10 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	close_game(t_game **game)
{
	free_cub3d(game);
	//exit(1);
}

int	handle_keyesc(t_data *data)
{
	close_game(&data->gm);
	mlx_destroy_image(data->mlx_ptr, data->tx_img[0].txt_img.img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->tx_img[1].txt_img.img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->tx_img[2].txt_img.img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->tx_img[3].txt_img.img_ptr);
	exit(1);
	return (0);
}
