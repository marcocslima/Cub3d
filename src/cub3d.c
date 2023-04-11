/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/11 15:43:55 by alida-si         ###   ########.fr       */
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
	if (key_code == 'p')
	{
		printf("# posição y: %f\n", game->player->y_position);
		printf("# posição x: %f\n", game->player->x_position);
	}
	return (1);
}

void	get_img(t_texture_img **txt_img, void *mlx_ptr, t_map_header *txt_path)
{
	int	aux;

	(*txt_img)->ea->mlx_img = mlx_xpm_file_to_image(mlx_ptr, txt_path->ea, &aux, &aux);
	(*txt_img)->no->mlx_img = mlx_xpm_file_to_image(mlx_ptr, txt_path->no, &aux, &aux);
	(*txt_img)->we->mlx_img = mlx_xpm_file_to_image(mlx_ptr, txt_path->we, &aux, &aux);
	(*txt_img)->so->mlx_img = mlx_xpm_file_to_image(mlx_ptr, txt_path->so, &aux, &aux);
}

void	get_img_addr(t_texture_img **txt_img)
{
	(*txt_img)->ea->addr = mlx_get_data_addr((*txt_img)->ea->mlx_img, &(*txt_img)->ea->bpp, &(*txt_img)->ea->line_len, &(*txt_img)->ea->endian);
	(*txt_img)->no->addr = mlx_get_data_addr((*txt_img)->no->mlx_img, &(*txt_img)->no->bpp, &(*txt_img)->no->line_len, &(*txt_img)->no->endian);
	(*txt_img)->we->addr = mlx_get_data_addr((*txt_img)->we->mlx_img, &(*txt_img)->we->bpp, &(*txt_img)->we->line_len, &(*txt_img)->we->endian);
	(*txt_img)->so->addr = mlx_get_data_addr((*txt_img)->so->mlx_img, &(*txt_img)->so->bpp, &(*txt_img)->so->line_len, &(*txt_img)->so->endian);
}

void	check_img_is_valid(t_texture_img *texture, t_game **game)
{
	if (texture->ea->mlx_img == NULL || texture->no->mlx_img == NULL || texture->we->mlx_img == NULL || texture->so->mlx_img == NULL)
		print_error_exit(game, "Invalid texture\n");
}

void	init_textures(t_game **game)
{
	get_img(&(*game)->texture_img, (*game)->mlx_data->mlx_ptr, (*game)->header);
	check_img_is_valid((*game)->texture_img, game);
	get_img_addr(&(*game)->texture_img);
}

void	get_player_position(t_game **game)
{
	int	i;
	int	j;

	i = 0;
	while((*game)->map->map[i])
	{
		j = 0;
		while((*game)->map->map[i][j])
		{
			if ((*game)->map->map[i][j] == 'N')
			{
				(*game)->player->x_position = j * MAP_CELL + MAP_CELL/2;
				(*game)->player->y_position = i * MAP_CELL + MAP_CELL/2;
				printf("y: %f x: %f\n", (*game)->player->y_position, (*game)->player->x_position);
				return ;
			}
			j++;
		}
		i++;
	}
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
		get_map(game->file, &game->map);
		get_header(&game);
		check_header(&game);
		verify_map(&game);
		print_whole_map(game);

		game->img_data->mlx_img = mlx_new_image(game->mlx_data->mlx_ptr,
				WINDOW_WIDTH, WINDOW_HEIGHT);
		game->img_data->addr = mlx_get_data_addr(game->img_data->mlx_img,
				&game->img_data->bpp, &game->img_data->line_len,
				&game->img_data->endian);

		init_textures(&game);
		get_player_position(&game);
		mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
		mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
		mlx_hook(game->mlx_data->mlx_win, 02, 1L << 0, handle_events, game);
		mlx_loop(game->mlx_data->mlx_ptr);
	}
	free_cub3d(&game);
	return (0);
}
