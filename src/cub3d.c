/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/28 05:07:38 by mcesar-d         ###   ########.fr       */
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

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLUE_SKY_PIXEL, FLOR_PIXEL);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	run_game(t_game *game)
{
	game->data.mlx_ptr = mlx_init();
	if (game->data.mlx_ptr == NULL)
		return (MLX_ERROR);
	game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (game->data.win_ptr == NULL)
	{
		free(game->data.win_ptr);
		return (MLX_ERROR);
	}

	game->data.img.mlx_img = mlx_new_image(game->data.mlx_ptr, WIDTH, HEIGHT);
	game->data.img.addr = mlx_get_data_addr(game->data.img.mlx_img, &game->data.img.bpp,
			&game->data.img.line_len, &game->data.img.endian);
	mlx_loop_hook(game->data.mlx_ptr, &render, &game->data);
	mlx_hook(game->data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game->data);
	mlx_loop(game->data.mlx_ptr);
	mlx_destroy_image(game->data.mlx_ptr, game->data.img.mlx_img);
	mlx_destroy_display(game->data.mlx_ptr);
	free(game->data.mlx_ptr);
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
		print_whole_map(game);
		run_game(game);
	}
	free_cub3d(&game);
	return (0);
}
