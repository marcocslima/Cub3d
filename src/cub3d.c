/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/15 16:18:13 by alida-si         ###   ########.fr       */
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

void	ray_casting(t_data *data)
{
	float	pixel;

	pixel = -1;
	while (++pixel < WIDTH)
	{
		ray_dir(pixel, data);
		calc_delta_dist(data);
		calc_side_dist(data);
		calc_dda(data);
		calc_perp_dist(data);
		calc_wall(data);
		run_textures(data, pixel);
	}
}

int	render_game(t_data *data)
{
	render_background(&data->img, BLUE_SKY_PIXEL, FLOR_PIXEL);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img_ptr, 0, 0);
	plot_map(data);
	return (0);
}

int	run_game(t_game *game)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->gm = game;
	data->mlx_ptr = mlx_init();
	load_textures(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (data->mlx_ptr == NULL || data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (MLX_ERROR);
	}
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->img.data = (int *)mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	mlx_hook(data->win_ptr, 2, 1L << 0, moving, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, end_game, data);
	mlx_loop_hook(data->mlx_ptr, &render_game, data);
	mlx_loop(data->mlx_ptr);
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
	ini_game_assets();
	init_player(game);
	run_game(game);
	return (0);
}
