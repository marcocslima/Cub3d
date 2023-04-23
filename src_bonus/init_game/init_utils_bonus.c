/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:19:59 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 16:37:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	get_ceiling_rgb(t_color *color, t_map_header *header)
{
	char	**temp;
	int		r;
	int		g;
	int		b;

	temp = ft_split(header->c, ',');
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	color->ceiling = (r << 16 | g << 8 | b);
	free_matrix(temp);
}

void	get_floor_rgb(t_color *color, t_map_header *header)
{
	char	**temp;
	int		r;
	int		g;
	int		b;

	temp = ft_split(header->f, ',');
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	color->floor = (r << 16 | g << 8 | b);
	free_matrix(temp);
}

void	get_background_rgb(t_game *game)
{
	get_ceiling_rgb(game->background_color, game->header);
	get_floor_rgb(game->background_color, game->header);
}

void	get_player_position(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->matrix[y][x] == 'N')
			{
				game->player.pos_x = (float)x + 0.5;
				game->player.pos_y = (float)y + 0.5;
				return ;
			}
		}
	}
}
