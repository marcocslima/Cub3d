/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:02:40 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/16 13:53:40 by alida-si         ###   ########.fr       */
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
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j])
		{
			if (map->matrix[i][j] != '1' && map->matrix[i][j] != '0'
			&& map->matrix[i][j] != ' ' && map->matrix[i][j] != 'N')
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
	verify_onlyspace_line(game);
}
