/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:22:44 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 16:37:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	print_error_exit(t_game **game, char *msg)
{
	print_error_msg(msg);
	close_game(game, EXIT_FAILURE);
}

void	print_error_msg(char *msg)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, RESET, ft_strlen(RESET));
}
