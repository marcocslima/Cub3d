/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_looking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:21:56 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/28 07:37:31 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	side_player_init(t_game *game)
{
	if (game->run == 0)
	{
		if (game->player.side_init == 'S')
			moving_direction(-PI, &game);
		if (game->player.side_init == 'W')
			moving_direction(-PI / 2, &game);
		if (game->player.side_init == 'E')
			moving_direction(+PI / 2, &game);
		game->run = 1;
	}
}

int	looking_down(float ray_dir_y)
{
	if (ray_dir_y > 0)
		return (1);
	return (0);
}

int	looking_right(float ray_dir_x)
{
	if (ray_dir_x > 0)
		return (1);
	return (0);
}

int	looking_left(float ray_dir_x)
{
	if (ray_dir_x < 0)
		return (1);
	return (0);
}

int	looking_up(float ray_dir_y)
{
	if (ray_dir_y < 0)
		return (1);
	return (0);
}
