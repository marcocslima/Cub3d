/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:05:47 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/12 15:06:48 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	verify_player(t_game **game)
{
	t_map	*map;
	int		nb_player;
	int		i;
	int		j;

	map = (*game)->map;
	nb_player = 0;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N')
				nb_player++;
			j++;
		}
		i++;
	}
	if (nb_player != 1)
		print_error_exit(game, "Invalid number of players\n");
}
