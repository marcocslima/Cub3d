/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:35 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/16 13:59:47 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
			printf("%c", game->map->matrix[i][j]);
		printf("\n");
	}
}
