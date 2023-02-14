/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:42:39 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/14 08:51:11 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	verify_top_and_bottom(t_game **game, char character)
{
	t_map	*map;

	map = (*game)->map;
	if (ft_strchr(map->map[0], character) != NULL)
		print_error_exit(game, "Find error on map...\n");
	if (ft_strchr(map->map[map->map_higth - 1], character) != NULL)
		print_error_exit(game, "Find error on map...\n");
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

void	verify_middle(t_game **game, char character)
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
			if (map->map[j][i] == character)
			{
				if (!verify_position(map, j, i))
					print_error_exit(game, "Find error on map...\n");
			}
			i++;
		}
		j++;
	}
}

void	verify_sides(t_game **game, char character)
{
	t_map	*map;
	int		i;

	map = (*game)->map;
	i = -1;
	while (++i < map->map_higth)
	{
		if (map->map[i][0] == character
			|| map->map[i][map->map_width - 1] == character)
			print_error_exit(game, "Find error on map...\n");
	}
}

void	verify_walls(t_game **game)
{
	verify_top_and_bottom(game, '0');
	verify_sides(game, '0');
	verify_middle(game, '0');
}
