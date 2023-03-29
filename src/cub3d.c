/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/29 14:28:38 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_file(int fd, t_game **game)
{
	char		*line;
	char		*ret;

	ret = get_next_line(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = ft_strjoin(ret, line);
		free(line);
	}
	close (fd);
	verify_empty_lines(ret, game);
	(*game)->file = ft_split(ret, '\n');
	free(ret);
}

void	move_direction(t_game *game, int key_code)
{
	if (key_code == LEFT_ARROW)
	{
		game->player->angle -= 0.1;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
	}
	if (key_code == RIGHT_ARROW)
	{
		game->player->angle += 0.1;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
	}
}

int	handle_events(int key_code, t_game *game)
{
	if (key_code == ESC)
		close_window(game);
	if (key_code == W)
		*&game->player->y_position -= 1;
	if (key_code == S)
		*&game->player->y_position += 1;
	if (key_code == A)
		*&game->player->x_position -= 1;
	if (key_code == D)
		*&game->player->x_position += 1;
	if (key_code == LEFT_ARROW || key_code == RIGHT_ARROW)
		move_direction(game, key_code);
	if (key_code == 'p')
	{
		printf("# posição y: %f\n", game->player->y_position);
		printf("# posição x: %f\n", game->player->x_position);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	*game;

	fd = check_input(argc, argv);
	init_data(&game);
	read_file(fd, &game);
	if (game->file != NULL)
	{
		get_map(game->file, &game->map);
		get_header(&game);
		check_header(&game);
		verify_map(&game);
		//print_whole_map(game);

		game->img_data->mlx_img = mlx_new_image(game->mlx_data->mlx_ptr,
				1500, 600);
		game->img_data->addr = mlx_get_data_addr(game->img_data->mlx_img,
				&game->img_data->bpp, &game->img_data->line_len,
				&game->img_data->endian);

		mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
		mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
		mlx_hook(game->mlx_data->mlx_win, 02, 1L << 0, handle_events, game);
		mlx_loop(game->mlx_data->mlx_ptr);
	}
	free_cub3d(&game);
	return (0);
}
