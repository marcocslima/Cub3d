/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:04:20 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/11 16:16:00 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceiling(t_game *game, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(game->img_data, j++, i, color);
		++i;
	}
}

void	render_floor(t_game *game, int color)
{
	int	i;
	int	j;

	i = WINDOW_HEIGHT / 2;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(game->img_data, j++, i, color);
		++i;
	}
}

void	render_background(t_game *game)
{
	int	i;
	int	j;

	if (game->mlx_data->mlx_win == NULL)
		return ;
	render_ceiling(game, COLOR_BLUE);
	render_floor(game, COLOR_GREEN);
}
