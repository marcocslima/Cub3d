/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:42:39 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 16:37:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	verify_top_and_bottom(t_game **game, char character)
{
	t_map	*map;

	map = (*game)->map;
	if (ft_strchr(map->matrix[0], character) != NULL)
		print_error_exit(game, "Find error on map...\n");
	if (ft_strchr(map->matrix[map->height - 1], character) != NULL)
		print_error_exit(game, "Find error on map...\n");
}

int	verify_position(t_map *map, int j, int i)
{
	if (map->matrix[j - 1][i] && map->matrix[j - 1][i] == ' ')
		return (0);
	if (map->matrix[j - 1][i - 1] && map->matrix[j - 1][i - 1] == ' ')
		return (0);
	if (map->matrix[j - 1][i + 1] && map->matrix[j - 1][i + 1] == ' ')
		return (0);
	if (map->matrix[j + 1][i] && map->matrix[j + 1][i] == ' ')
		return (0);
	if (map->matrix[j + 1][i - 1] && map->matrix[j + 1][i - 1] == ' ')
		return (0);
	if (map->matrix[j + 1][i + 1] && map->matrix[j + 1][i + 1] == ' ')
		return (0);
	if (map->matrix[j][i - 1] && map->matrix[j][i - 1] == ' ')
		return (0);
	if (map->matrix[j][i + 1] && map->matrix[j][i + 1] == ' ')
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
	while (j < map->height - 1)
	{
		i = 0;
		while (i < map->width)
		{
			if (map->matrix[j][i] == character)
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
	while (++i < map->height)
	{
		if (map->matrix[i][0] == character
			|| map->matrix[i][map->width - 1] == character)
			print_error_exit(game, "Find error on map...\n");
	}
}

void	verify_walls(t_game **game)
{
	verify_top_and_bottom(game, '0');
	verify_sides(game, '0');
	verify_middle(game, '0');
}
