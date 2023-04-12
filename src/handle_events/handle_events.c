/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:32:25 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/11 22:33:07 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_direction(t_game *game, int key_code)
{
	if (key_code == LEFT_ARROW)
	{
		game->player->angle -= ANGLE_STEP;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
	}
	if (key_code == RIGHT_ARROW)
	{
		game->player->angle += ANGLE_STEP;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
	}
}

int	handle_events(int key_code, t_game *game)
{
	if (key_code == ESC)
		close_window(game);
	if (key_code == W)
		*&game->player->y_position -= PLAYER_STEP;
	if (key_code == S)
		*&game->player->y_position += PLAYER_STEP;
	if (key_code == A)
		*&game->player->x_position -= PLAYER_STEP;
	if (key_code == D)
		*&game->player->x_position += PLAYER_STEP;
	if (key_code == LEFT_ARROW || key_code == RIGHT_ARROW)
		move_direction(game, key_code);
	return (1);
}
