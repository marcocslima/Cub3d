/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:21:56 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 15:28:11 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
