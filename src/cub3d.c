/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/11 22:23:09 by alida-si         ###   ########.fr       */
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

void	get_player_position(t_game **game)
{
	int	i;
	int	j;

	i = 0;
	while ((*game)->map->map[i])
	{
		j = 0;
		while ((*game)->map->map[i][j])
		{
			if ((*game)->map->map[i][j] == 'N')
			{
				(*game)->player->x_position = j * MAP_CELL + MAP_CELL / 2;
				(*game)->player->y_position = i * MAP_CELL + MAP_CELL / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	parser(t_game **game)
{
	get_map((*game)->file, &(*game)->map);
	get_header(game);
	check_header(game);
	verify_map(game);
}

void	create_window_img(t_game **game)
{
	(*game)->img_data->mlx_img = mlx_new_image((*game)->mlx_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	(*game)->img_data->addr = mlx_get_data_addr((*game)->img_data->mlx_img,
			&(*game)->img_data->bpp, &(*game)->img_data->line_len,
			&(*game)->img_data->endian);
}

void	game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
	mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
	mlx_hook(game->mlx_data->mlx_win, 02, 1L << 0, handle_events, game);
	mlx_loop(game->mlx_data->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	int		fd;
	int		aux;
	t_game	*game;

	fd = check_input(argc, argv);
	init_data(&game);
	read_file(fd, &game);
	if (game->file != NULL)
	{
		parser(&game);
		init_data_mlx(&game->mlx_data);
		create_window_img(&game);
		init_textures(&game);
		get_player_position(&game);
		game_loop(game);
	}
	free_cub3d(&game);
	return (0);
}
