/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/07 02:06:08 by mcesar-d         ###   ########.fr       */
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

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_img *img, int cceil, int cflor)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			img_pix_put(img, j++, i, cflor);
	}
	i = -1;
	while (++i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
			img_pix_put(img, j++, i, cceil);
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	plot_map(t_data *data)
{
	int	i;
	int	j;
	int	color;
	int	side;

	i = -1;
	side = 15;
	while(++i < data->gm->map->map_higth)
	{
		j = -1;
		while(++j < data->gm->map->map_width)
		{
			color = BLACK_PIXEL;
			if(data->gm->map->map[i][j] == '1')
				color = BRICK_PIXEL;
			if(data->gm->map->map[i][j] == '0' || data->gm->map->map[i][j] == 'N')
				color = BEIGE_PIXEL;
			render_rect(&data->img, (t_rect){j * side, i * side, side, side, color});
			render_rect(&data->img, (t_rect){data->gm->player.pos[0] * side, data->gm->player.pos[1] * side, 5, 5, RED_PIXEL});
			render_rect(&data->img, (t_rect){j * side, i * side, 1, side, BLUE_SKY_PIXEL});
			render_rect(&data->img, (t_rect){j * side, i * side, side, 1, BLUE_SKY_PIXEL});
		}
	}
}

int looking(float ang, t_data *data)
{
	float	tmp;
	float	tmp_plane;

	tmp = cos(ang) * data->gm->player.dir[0] - sin(ang) * data->gm->player.dir[1];
	data->gm->player.dir[1] = sin(ang) * data->gm->player.dir[0] + cos(ang)
		* data->gm->player.dir[1];
	data->gm->player.dir[0] = tmp;
	tmp_plane = cos(ang) * data->gm->player.cam_plane[0]
		- sin(ang) * data->gm->player.cam_plane[1];
	data->gm->player.cam_plane[1] = sin(ang) * data->gm->player.cam_plane[0]
		+ cos(ang) * data->gm->player.cam_plane[1];
	data->gm->player.cam_plane[0] = tmp_plane;
	return(0);
}

int moving(int key, t_data *data)
{
	int		tmp_0;
	int		tmp_1;
	float	desloc;

	desloc = 0.1;
	if (key == A)
	{
		tmp_0 = (int)(data->gm->player.pos[0] + data->gm->player.dir[1] * 0.5);
		tmp_1 = (int)(data->gm->player.pos[1] - data->gm->player.dir[0] * 0.5);
		if(data->gm->map->map[tmp_1][tmp_0] != '1')
		{
			data->gm->player.pos[0] += data->gm->player.dir[1] * desloc;
			data->gm->player.pos[1] -= data->gm->player.dir[0] * desloc;
		}
	}
	if (key == D)
	{
		tmp_0 = (int)(data->gm->player.pos[0] - data->gm->player.dir[1] * 0.5);
		tmp_1 = (int)(data->gm->player.pos[1] + data->gm->player.dir[0] * 0.5);
		if(data->gm->map->map[tmp_1][tmp_0] != '1')
		{
			data->gm->player.pos[0] -= data->gm->player.dir[1] * desloc;
			data->gm->player.pos[1] += data->gm->player.dir[0] * desloc;
		}
	}
	if (key == W)
	{
		tmp_0 = (int)(data->gm->player.pos[0] + data->gm->player.dir[0] * 0.5);
		tmp_1 = (int)(data->gm->player.pos[1] + data->gm->player.dir[1] * 0.5);
		if(data->gm->map->map[tmp_1][tmp_0] != '1')
		{
			data->gm->player.pos[0] += data->gm->player.dir[0] * desloc;
			data->gm->player.pos[1] += data->gm->player.dir[1] * desloc;
		}
	}
	if (key == S)
	{
		tmp_0 = (int)(data->gm->player.pos[0] - data->gm->player.dir[0] * 0.5);
		tmp_1 = (int)(data->gm->player.pos[1] - data->gm->player.dir[1] * 0.5);
		if(data->gm->map->map[tmp_1][tmp_0] != '1')
		{
			data->gm->player.pos[0] -= data->gm->player.dir[0] * desloc;
			data->gm->player.pos[1] -= data->gm->player.dir[1] * desloc;
		}
	}
	if (key == 65361)
		looking(- PI / 100, data);
	if (key == 65363)
		looking(+ PI / 100, data);
	return(0);
}

int	render(t_data *data)
{
	if (data->gm->map->map_higth <= data->gm->map->map_width)
		data->l_side = HEIGHT / data->gm->map->map_width;
	else
		data->l_side = WIDTH / data->gm->map->map_higth;
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLUE_SKY_PIXEL, FLOR_PIXEL);
	plot_map(data);

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
		set_texture(data, pixel);
		
		int color;
		if(data->gm->dda.hitSide == 1)
			color = GRAY1_PIXEL;
		else if(data->gm->dda.hitSide == 0)
			color = GRAY2_PIXEL;
		
		float d = 0.01;
		while(d < 1)
		{
			render_rect(&data->img, (t_rect){(data->gm->player.pos[0] * 15) + 
				(15 * data->gm->ray.dir_x * d * data->gm->dda.perp_dist),
				(data->gm->player.pos[1] * 15) + 
				(15 * data->gm->ray.dir_y * d  * data->gm->dda.perp_dist), 1, 1, GREEN_PIXEL});
			d = d + 0.001;
		}

		// render_rect(&data->img, (t_rect){(pixel) + 
		// 	(data->gm->ray.dir_x),
		// 	(data->gm->dda.line_start) + 
		// 	(data->gm->ray.dir_y), 1, data->gm->dda.wall_line_height, color});
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

void	init_player(t_game *game)
{
	int	x;
	int	y;

	game->player.dir[0] = 0;
	game->player.dir[1] = -1;
	game->player.cam_plane[0] = 0.66;
	game->player.cam_plane[1] = 0;
	y = -1;
	while(++y < game->map->map_higth)
	{
		x = -1;
		while(++x < game->map->map_width)
		{
			if (game->map->map[y][x] == 'N')
			{
				game->player.pos[0] = (float)x + 0.5;
				game->player.pos[1] = (float)y + 0.5;
				return ;
			}
		}
	}
}

int	run_game(t_game *game)
{
	t_data *data;

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
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data->win_ptr, 2, 1L << 0, moving, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return(0);
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
		//print_map(game);
		init_player(game);
		run_game(game);
	}
	free_cub3d(&game);
	return (0);
}
