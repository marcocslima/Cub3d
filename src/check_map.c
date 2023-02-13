/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:24:57 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/12 21:25:01 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	verify_head_and_foot(t_game **game)
{
	t_map	*map;

	map = (*game)->map;
	if (ft_strchr(map->map[0], '0') != NULL)
		print_error_exit(game, "find error on map...\n");
	if (ft_strchr(map->map[map->map_higth - 1], '0') != NULL)
		print_error_exit(game, "find error on map...\n");
}

int	verify_position(t_map *map, int j, int i)
{
	if (map->map[j - 1][i] && map->map[j - 1][i] == ' ')
		return (0);
	if (map->map[j - 1][i - 1] && map->map[j - 1][i - 1] == ' ')
		return (0);
	if (map->map[j - 1][i + 1] && map->map[j - 1][i + 1] == ' ')
		return (0);
	if (map->map[j + 1][i] && map->map[j + 1][i] == ' ')
		return (0);
	if (map->map[j + 1][i - 1] && map->map[j + 1][i - 1] == ' ')
		return (0);
	if (map->map[j + 1][i + 1] && map->map[j + 1][i + 1] == ' ')
		return (0);
	if (map->map[j][i - 1] && map->map[j][i - 1] == ' ')
		return (0);
	if (map->map[j][i + 1] && map->map[j][i + 1] == ' ')
		return (0);
	return (1);
}

void	verify_holes(t_game **game)
{
	int		i;
	int		j;
	t_map	*map;

	j = 1;
	map = (*game)->map;
	while (j < map->map_higth - 1)
	{
		i = 0;
		while (i < map->map_width)
		{
			if (map->map[j][i] == '0')
			{
				if (!verify_position(map, j, i))
					print_error_exit(game, "find error on map...\n");
			}
			i++;
		}
		j++;
	}
}

void	verify_sides(t_game **game)
{
	t_map	*map;
	int		i;

	map = (*game)->map;
	i = -1;
	while (++i < map->map_higth)
	{
		if (map->map[i][0] == '0' || map->map[i][map->map_width - 1] == '0')
			print_error_exit(game, "find error on map...\n");
	}
}

void	verify_map(t_game **game)
{
	verify_head_and_foot(game);
	verify_sides(game);
	verify_holes(game);
	verify_onlyspace_line(game);
}
