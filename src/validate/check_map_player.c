/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:34:15 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/28 06:04:57 by mcesar-d         ###   ########.fr       */
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
	int		i;
	int		count;
	t_map	*map;
	char	*type_players;

	i = -1;
	count = 0;
	type_players = "NSWE";
	map = (*game)->map;
	while (++i < 4)
		if (char_occurrence_matrix(map->matrix, type_players[i]) == 1)
			count++;
	if (count != 1)
		print_error_exit(game, "Invalid number of players\n");
}

void	verify_player(t_game **game)
{
	verify_nb_player(game);
	verify_top_and_bottom(game, 'N');
	verify_sides(game, 'N');
	verify_middle(game, 'N');
}
