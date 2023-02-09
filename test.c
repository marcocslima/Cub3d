/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:35 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/08 20:31:53 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
