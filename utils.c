/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:22:44 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/05 13:00:39 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error_msg(char *msg)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, RESET, ft_strlen(RESET));
}
