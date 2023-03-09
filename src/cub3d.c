/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/09 10:07:43 by alida-si         ###   ########.fr       */
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

int	handle_events(int key_code, t_game *game)
{
	if (key_code == 65307)
		close_window(game);
	if (key_code == W)
		*&game->img_data->y_position -= 5;
	if (key_code == S)
		*&game->img_data->y_position += 5;
	if (key_code == A)
		*&game->img_data->x_position -= 5;
	if (key_code == D)
		*&game->img_data->x_position += 5;
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

		game->img_data->mlx_img = mlx_new_image(game->mlx_data->mlx_ptr, 1000, 500);
		game->img_data->addr = mlx_get_data_addr(game->img_data->mlx_img, &game->img_data->bpp, &game->img_data->line_len, &game->img_data->endian);

		mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
		mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
		mlx_hook(game->mlx_data->mlx_win, 02, 1L << 0, handle_events, game);
		mlx_loop(game->mlx_data->mlx_ptr);
	}
	free_cub3d(&game);
	return (0);
}
