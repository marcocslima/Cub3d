/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:35 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/07 19:17:28 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_whole_map(t_game *game)
{
	int	i;

	i = -1;
	printf("HEADER\n");
	printf("%s\n", game->header->no);
	printf("%s\n", game->header->so);
	printf("%s\n", game->header->we);
	printf("%s\n", game->header->ea);
	printf("%s\n", game->header->f);
	printf("%s\n\n", game->header->c);
	printf("MAP\n");
	while (game->map->map[++i])
		printf("%s\n", game->map->map[i]);
}
