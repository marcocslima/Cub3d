/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:02:40 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/12 15:12:06 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	verify_invalid_char(t_game **game)
{
	t_map	*map;
	int		i;
	int		j;

	i = 0;
	map = (*game)->map;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
			&& map->map[i][j] != ' ' && map->map[i][j] != 'N')
				print_error_exit(game, "Invalid character inside map\n");
			j++;
		}
		i++;
	}
}

void	verify_map(t_game **game)
{
	verify_invalid_char(game);
	verify_walls(game);
	verify_player(game);
}
