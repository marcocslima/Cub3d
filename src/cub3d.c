/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/23 13:40:55 by alida-si         ###   ########.fr       */
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

void	ray_casting(t_game *game)
{
	float	pixel;

	pixel = -1;
	while (++pixel < WIDTH)
	{
		ray_dir(pixel, &game);
		get_offsets(&game);
		calc_dda(&game);
		calc_perp_dist(&game);
		calc_wall_height(&game);
		render_textured_walls(&game, pixel);
	}
}

int	render_game(t_game *game)
{
	render_background(game->img, game->background_color);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx->ptr, game->mlx->win,
		game->img->img_ptr, 0, 0);
	plot_map(game);
	return (0);
}

int	run_game(t_game *game)
{
	mlx_hook(game->mlx->win, 2, 1L << 0, moving, game);
	mlx_hook(game->mlx->win, 17, 1L << 17, end_game, &game);
	mlx_loop_hook(game->mlx->ptr, &render_game, game);
	mlx_loop(game->mlx->ptr);
	return (0);
}

void	parse_map_file(t_game **game, int argc, char **argv)
{
	int		fd;

	fd = check_input(argc, argv);
	read_file(fd, game);
	if ((*game)->file != NULL)
	{
		get_map((*game)->file, &(*game)->map);
		get_header(game);
		check_header(game);
		verify_map(game);
		return ;
	}
	free_cub3d(game);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	init_data(&game);
	parse_map_file(&game, argc, argv);
	init_game_assets(&game);
	run_game(game);
	return (0);
}
