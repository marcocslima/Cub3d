/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/02 11:59:50 by alida-si         ###   ########.fr       */
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

int	close_window(t_game *game)
{
	printf("entrou aqui\n");
	mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win);
	mlx_destroy_display(game->mlx_data->mlx_ptr);
	free(game->mlx_data->mlx_ptr);
	close_game(&game);
}

int	handle_events(int key_code, t_game *game)
{
	if (key_code == 65307)
		close_window(game);
	return (1);
}

int	render_rect(t_game *game)
{
	int	i;
	int	j;

	if (game->mlx_data->mlx_win == NULL)
		return (1);
	i = 250;
	while (i < 250 + 8)
	{
		j = 250;
		while (j < 250 + 8)
			mlx_pixel_put(game->mlx_data->mlx_ptr, game->mlx_data->mlx_win,
				j++, i, 0xFF0000);
		++i;
	}
	return (0);
}

int	render(t_game *game)
{
	//if window has been destroyed, we don't want to put the pixel !
	/*if (game->mlx_win != NULL)
		mlx_pixel_put(game->mlx_ptr, game->mlx_win, 500/2, 500/2, 0xFF0000);
	return (0);*/
	render_rect(game);
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
		mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
		mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
		mlx_key_hook(game->mlx_data->mlx_win, handle_events, game);
		mlx_loop(game->mlx_data->mlx_ptr);
	}
	free_cub3d(&game);
	return (0);
}
