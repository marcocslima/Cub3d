/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:05:47 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/12 15:35:10 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	char_occurrence_matrix(char **matrix, char character)
{
	int		nb_char;
	int		i;
	int		j;

	nb_char = 0;
	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
		{
			if (matrix[i][j] == character)
				nb_char++;
		}
	}
	return (nb_char);
}

void	verify_nb_player(t_game **game)
{
	t_map	*map;

	map = (*game)->map;
	if (char_occurrence_matrix(map->map, 'N') != 1)
		print_error_exit(game, "Invalid number of players\n");
}

void	verify_player(t_game **game)
{
	verify_nb_player(game);
	verify_top_and_bottom(game, 'N');
	verify_sides(game, 'N');
	verify_middle(game, 'N');
}
