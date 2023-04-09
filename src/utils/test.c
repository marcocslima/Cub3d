/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:35 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/09 16:27:58 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_whole_map(t_game *game)
{
	int	i;

	i = -1;
	printf("HEADER\n");
	printf("%s  %s\n", game->header->no[0], game->header->no[1]);
	printf("%s  %s\n", game->header->so[0], game->header->so[1]);
	printf("%s  %s\n", game->header->we[0], game->header->we[1]);
	printf("%s  %s\n", game->header->ea[0], game->header->ea[1]);
	printf("%s   %s\n", game->header->f[0], game->header->f[1]);
	printf("%s   %s\n\n", game->header->c[0], game->header->c[1]);
	printf("MAP\n");
	while (game->map->map[++i])
		printf("%s\n", game->map->map[i]);
}

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
