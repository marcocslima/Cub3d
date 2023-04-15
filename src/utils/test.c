/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:35 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/15 19:07:02 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map->map_higth)
	{
		j = -1;
		while (++j < game->map->map_width)
			printf("%c", game->map->map[i][j]);
		printf("\n");
	}
}
