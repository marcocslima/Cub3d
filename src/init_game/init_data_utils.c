/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:19:59 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/22 14:47:07 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
