/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/04 04:50:58 by mcesar-d         ###   ########.fr       */
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
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
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
	side = data->l_side;
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
			render_rect(&data->img, (t_rect){data->gm->player.pos[0] * side + data->gm->player.dir[0], data->gm->player.pos[1] * side + data->gm->player.dir[1], 3, 3, BLUE_PIXEL});
			render_rect(&data->img, (t_rect){j * side, i * side, 1, side, BLUE_SKY_PIXEL});
			render_rect(&data->img, (t_rect){j * side, i * side, side, 1, BLUE_SKY_PIXEL});
		}
	}
}

int looking(int key, t_data *data)
{
	if (key == 65361)
	{
		data->gm->ang -= 0.1;
		if(data->gm->ang < 0)
			data->gm->ang += 2 * PI;
	 	data->gm->player.dir[0] = cos(data->gm->ang) * 20;
		data->gm->player.dir[1] = sin(data->gm->ang) * 20;
	}
	if (key == 65363)
	{
		data->gm->ang += 0.1;
		if(data->gm->ang > 2 * PI)
			data->gm->ang -= 2 * PI;
	 	data->gm->player.dir[0] = cos(data->gm->ang) * 20;
		data->gm->player.dir[1] = sin(data->gm->ang) * 20;
	}
	return(0);
}

int moving(int key, t_data *data)
{
	if (key == A)
		data->gm->player.pos[0] = data->gm->player.pos[0] - 0.1;
	if (key == D)
		data->gm->player.pos[0] = data->gm->player.pos[0] + 0.1;
	if (key == W)
		data->gm->player.pos[1] = data->gm->player.pos[1] - 0.1;
	if (key == S)
		data->gm->player.pos[1] = data->gm->player.pos[1] + 0.1;
	if (key == 65361 || key == 65363)
		looking(key, data);
	printf("pos: %f # %f | dir: %f # %f\n\n",data->gm->player.pos[0],data->gm->player.pos[1],data->gm->player.dir[0],data->gm->player.dir[1]);
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
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
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (MLX_ERROR);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data->win_ptr, 2, 1L << 0, moving, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
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
		//check_header(&game);
		verify_map(&game);
		//print_whole_map(game);
		print_map(game);
		init_player(game);
		run_game(game);
	}
	free_cub3d(&game);
	return (0);
}
