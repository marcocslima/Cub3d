/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/04 16:06:03 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_game *game);
int	render_rect(t_game *game);
void	render_background(t_game *game, int color);

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

int	close_window(t_game *game)
{
	printf("fechar janela\n");
	mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win);
	mlx_destroy_display(game->mlx_data->mlx_ptr);
	free(game->mlx_data->mlx_ptr);
	close_game(&game);
}

int	handle_events(int key_code, t_game *game)
{
	if (key_code == 65307)
		close_window(game);
	if (key_code == W)
		*&game->img->y_position -= 5;
	if (key_code == S)
		*&game->img->y_position += 5;
	if (key_code == A)
		*&game->img->x_position -= 5;
	if (key_code == D)
		*&game->img->x_position += 5;
	render(game);
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

		game->img->mlx_img = mlx_new_image(game->mlx_data->mlx_ptr, 500, 500);
		game->img->addr = mlx_get_data_addr(game->img->mlx_img, &game->img->bpp, &game->img->line_len, &game->img->endian);

		mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
		mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
		mlx_hook(game->mlx_data->mlx_win, 02, 1L << 0, handle_events, game);
		mlx_loop(game->mlx_data->mlx_ptr);
	}
	free_cub3d(&game);
	return (0);
}
