/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:42:55 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/13 14:20:28 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	looking_up(double angle)
{
	if (angle >= PI && angle <= 2 * PI)
		return (1);
	return (0);
}

int	looking_right(double angle)
{
	if (angle > 3 * PI / 2 || angle < PI / 2)
		return (1);
	return (0);
}

double	deg_to_rad(double degress)
{
	return (degress * (PI / 180.0));
}
