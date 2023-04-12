/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:30:44 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/11 22:37:17 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data_mlx(t_data **mlx_data)
{
	*mlx_data = (t_data *) malloc(sizeof(t_data));
	(*mlx_data)->mlx_ptr = mlx_init();
	(*mlx_data)->mlx_win = mlx_new_window((*mlx_data)->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
}

void	init_data_texture_img(t_texture_img **texture_img)
{
	*texture_img = (t_texture_img *) malloc(sizeof(t_texture_img));
	init_data_img(&(*texture_img)->ea);
	init_data_img(&(*texture_img)->no);
	init_data_img(&(*texture_img)->so);
	init_data_img(&(*texture_img)->we);
}

void	init_data_img(t_img **img)
{
	*img = (t_img *) malloc(sizeof(t_img));
	(*img)->mlx_img = NULL;
	(*img)->addr = NULL;
	(*img)->bpp = 0;
	(*img)->endian = 0;
	(*img)->line_len = 0;
}

void	get_player_position(t_game **game)
{
	int	i;
	int	j;

	i = 0;
	while ((*game)->map->map[i])
	{
		j = 0;
		while ((*game)->map->map[i][j])
		{
			if ((*game)->map->map[i][j] == 'N')
			{
				(*game)->player->x_position = j * MAP_CELL + MAP_CELL / 2;
				(*game)->player->y_position = i * MAP_CELL + MAP_CELL / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}
